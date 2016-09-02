#include "ballsystem.h"
#include "object.h"
#include "video.h"
#include "collision.h"
#include "bricks.h"
#include "particles.h"
#include "rumble.h"

#define RUMBLE_TIME 15

BallSystem::BallSystem() : System<Physics>()
{
	manage_comp = false;
}

static void createBrickBreakParticles(Transform* parent, FIXED x, FIXED y)
{
	Object* o = new Object(parent);	//deleted by particle component
	if(o == nullptr) return;
	o->setPosition(x, y);
	auto pt_c = o->addComponent<Particles>();
	pt_c->startParticles(24, 0, 512, 1, 30, { ATTR0_SQUARE, ATTR1_SIZE_8x8, 8|(1<<ATTR2_PALBANK_SHIFT) });
}

static void createPaddleParticles(Transform* parent, FIXED x, FIXED y)
{
	Object* o = new Object(parent);	//deleted by particle component
	if(o == nullptr) return;
	o->setPosition(x, y);
	auto pt_c = o->addComponent<Particles>();
	pt_c->startParticles(24, 384, 256, 2, 20, { ATTR0_SQUARE, ATTR1_SIZE_8x8, 8|(4<<ATTR2_PALBANK_SHIFT) });
}

static bool ballCollisionBricks(RECT& ball, Transform* cam)
{
	RECT br_collider;

	//TODO: only check necessary bricks
	int x,y;
	for(y = 0;  y < BRICKS_VERTICAL; y++)
	{
		for(x = 0; x < BRICKS_HORIZONTAL; x++)
		{
			getBrickCollider(x, y, br_collider);

			u8* brick = &bricks_alive[x + y*BRICKS_HORIZONTAL];

			if(*brick)
			{
				if(checkCollision(ball, br_collider))
				{
					*brick = 0;
					createBrickBreakParticles(cam, br_collider.left + 8, br_collider.top + 4);
					return true;
				}
			}
		}
	}

	return false;
}

//actually uses a System<Physics> but cast to allow access to private members
bool BallSystem::ballCollision(BallSystem* phys_sys, Physics* comp, RECT& test_c, bool& is_test_c)
{
	auto& comp_list = phys_sys->comp_list;

	RECT collider;
	comp->getTranslatedCollider(collider);

	//bounce off paddle (and other Physics if any)
	for(auto it = comp_list.begin(); it != comp_list.end(); it++)
	{
		auto c2 = (Physics*)*it;
		if(c2 != comp && c2->getParent() != nullptr)
		{
			RECT collider2;
			c2->getTranslatedCollider(collider2);

			if(checkCollision(collider,collider2))
			{
				//createPaddleParticles(comp->getParent()->getParent(), collider2.left+16, collider2.top);
				test_c = collider2;
				is_test_c = true;
				return true;
			}
		}
	}

	//ball hit bricks
	return ballCollisionBricks(collider, comp->getParent()->getParent());

	//return false;
}

#define createPaddleParticlesFull() createPaddleParticles(comp->getParent()->getParent(), test_c.left+16, test_c.top)

void BallSystem::update()
{
	for(auto it = comp_list.begin(); it != comp_list.end(); it++)
	{
		auto comp = (Physics*)*it;

		Object* parent = comp->getParent();
		RECT collider;

		if(parent == nullptr) break;

		//move back and check each axis separately
		parent->x -= comp->xspeed;
		parent->y -= comp->yspeed;

		RECT test_c;
		bool is_test_c = false;

		//check horizontal collisions
		parent->x += comp->xspeed;
		if(ballCollision((BallSystem*)Physics::getSystem(), comp, test_c, is_test_c))
		{
			parent->x -= comp->xspeed;
			comp->xspeed *= -1;

			//if no longer colliding to prevent constant particles spawning
			comp->getTranslatedCollider(collider);
			if(is_test_c && !checkCollision(collider,test_c))
			{
				createPaddleParticlesFull();
			}
		}

		is_test_c = false;
		//check vertical collisions
		parent->y += comp->yspeed;
		if(ballCollision((BallSystem*)Physics::getSystem(), comp, test_c, is_test_c))
		{
			parent->y -= comp->yspeed;
			comp->yspeed *= -1;

			//if no longer colliding to prevent constant particles spawning
			comp->getTranslatedCollider(collider);
			if(is_test_c && !checkCollision(collider,test_c))
			{
				createPaddleParticlesFull();
			}
		}

		comp->getTranslatedCollider(collider);

		//horizontal bounds check
		if(collider.left < SCREEN_LEFT)
		{
			parent->x += SCREEN_LEFT - collider.left;
			comp->xspeed *= -1;
			Rumble::sendRumbleMessage(RUMBLE_TIME, true, false);
		}
		else if(collider.right > SCREEN_RIGHT)
		{
			parent->x += SCREEN_RIGHT - collider.right;
			comp->xspeed *= -1;
			Rumble::sendRumbleMessage(RUMBLE_TIME, true, false);
		}

		//vertical bounds check
		if(collider.top < SCREEN_TOP)
		{
			parent->y += SCREEN_TOP - collider.top;
			comp->yspeed *= -1;
			Rumble::sendRumbleMessage(RUMBLE_TIME, false, true);
		}
		else if(collider.bottom > SCREEN_BOTTOM)
		{
			parent->y += SCREEN_BOTTOM - collider.bottom;
			comp->yspeed *= -1;
			Rumble::sendRumbleMessage(RUMBLE_TIME, false, true);
		}
	}
}
