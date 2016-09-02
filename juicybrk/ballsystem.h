#ifndef _BALL_SYSTEM_H_
#define _BALL_SYSTEM_H_
#include "system.h"
#include "physics.h"

class BallSystem : public System<Physics>
{
private:
	static bool ballCollision(BallSystem* phys_sys, Physics* comp, RECT& test_c, bool& is_test_c);
public:
	BallSystem();

	void update();
};

#endif
