#ifndef _PHYSICS_COMPONENT_H_
#define _PHYSICS_COMPONENT_H_
#include "component.h"
extern "C" {
#include <tonc_math.h>
}

class Physics : public Component<Physics>
{
public:
	FIXED xspeed, yspeed;
	RECT collider;

	Physics();
	~Physics();

	void update();
	void getTranslatedCollider(RECT& r);

	inline void setCollider(int left,int top,int right,int bottom) {
		collider = {left, top, right, bottom};
	}
};

#endif
