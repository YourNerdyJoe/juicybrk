#include "physics.h"
#include "object.h"

Physics::Physics() : Component<Physics>(), xspeed(0), yspeed(0), collider({0,0,8,8})
{
}

Physics::~Physics()
{
}

void Physics::update()
{
	parent->x += xspeed;
	parent->y += yspeed;
}

void Physics::getTranslatedCollider(RECT& r)
{
	r = collider;

	r.left		+= parent->x;
	r.top		+= parent->y;
	r.right		+= parent->x;
	r.bottom	+= parent->y;
}
