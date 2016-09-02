#include "playerinputsystem.h"
#include "object.h"
#include <tonc.h>
#include "video.h"

PlayerInputSystem::PlayerInputSystem() : System<Physics>()
{
	manage_comp = false;
}

void PlayerInputSystem::update()
{
	if(comp_list.empty()) return;

	auto comp = (Physics*)comp_list.back();
	auto parent = comp->getParent();
	if(parent == nullptr) return;

	comp->xspeed = 0;
	if(key_is_down(KEY_RIGHT))
	{
		comp->xspeed += PLAYER_SPEED;
	}
	if(key_is_down(KEY_LEFT))
	{
		comp->xspeed -= PLAYER_SPEED;
	}

	int x = parent->x + comp->xspeed;
	RECT& collider = comp->collider;

	//bounds check
	if(x + collider.left < SCREEN_LEFT)
	{
		parent->x = SCREEN_LEFT - collider.left - comp->xspeed;
	}
	else if(x + collider.right > SCREEN_RIGHT)
	{
		parent->x = SCREEN_RIGHT - collider.right - comp->xspeed;
	}
}
