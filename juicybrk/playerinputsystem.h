#ifndef _PLAYER_INPUT_SYSTEM_H_
#define _PLAYER_INPUT_SYSTEM_H_
#include "system.h"
#include "physics.h"

#define PLAYER_SPEED 4

class PlayerInputSystem : public System<Physics>
{
public:
	PlayerInputSystem();

	void update();
};

#endif
