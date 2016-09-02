#include "rumble.h"
#include "object.h"

Rumble::Rumble() : rumble_time(0), xaxis(false), yaxis(false)
{
}

void Rumble::update()
{
	if(rumble_time > 0)
	{
		int ofs = (rumble_time & 3) - 2;	//time % 4 - 2
		if(rumble_time & 4) ofs *= -1;

		if(xaxis) parent->x = ofs;
		if(yaxis) parent->y = ofs;

		rumble_time--;
	}
	else
	{
		xaxis = false;
		yaxis = false;
	}
}

void Rumble::startRumble(int time, bool x, bool y)
{
	rumble_time += time;
	if(x) xaxis = true;
	if(y) yaxis = true;
}

void RumbleSystem::sendRumbleMessage(int time, bool x, bool y)
{
	for(auto it = comp_list.begin(); it != comp_list.end(); it++)
	{
		auto comp = (Rumble*)*it;
		comp->startRumble(time, x, y);
	}
}
