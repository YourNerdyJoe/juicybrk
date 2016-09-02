#ifndef _RUMBLE_COMPONENT_H_
#define _RUMBLE_COMPONENT_H_
#include "component.h"

class Rumble;

class RumbleSystem : public System<Rumble>
{
public:
	void sendRumbleMessage(int time, bool x, bool y);
};

class Rumble : public Component<Rumble>
{
	int rumble_time;
	bool xaxis,yaxis;
public:
	Rumble();

	void update();
	void startRumble(int time, bool x, bool y);

	static inline void sendRumbleMessage(int time, bool x, bool y) {
		((RumbleSystem*)system)->sendRumbleMessage(time, x, y);
	}
};

#endif
