#include "particles.h"
#include <stdlib.h>
#include "video.h"
#include "object.h"

Particles::Particles() : particles(nullptr), max_particles(0), direction(0), direction_range(0), max_speed(0), lifetime(0)
{
}

Particles::~Particles()
{
	if(particles) delete[] particles;
}

void Particles::startParticles(uint num_p, FIXED dir, FIXED dir_range, FIXED max_spd, int life, OBJ_ATTR oam_obj)
{
	max_particles = num_p;
	particles = new Particle[max_particles];

	direction = dir;
	direction_range = dir_range;

	max_speed = max_spd;

	lifetime = life;

	obj = oam_obj;

	int i;
	for(i = 0; i < max_particles; i++)
	{
		particles[i].pos = { 0, 0 };

		FIXED c_speed = rand() % (max_speed<<8) + 1;
		FIXED c_direction = rand() % (direction_range<<7);
		c_direction += (direction - direction_range/2)<<7;

		particles[i].speed.x = (c_speed * lu_cos(c_direction))>>8;	//.12f
		particles[i].speed.y = (c_speed * lu_sin(c_direction))>>8;	//.12f
	}
}

void Particles::update()
{
	if(lifetime <= 0)
	{
		delete parent;
		return;
	}

	int i;
	for(i = 0; i < max_particles; i++)
	{
		particles[i].pos.x += particles[i].speed.x;	//.12f
		particles[i].pos.y += particles[i].speed.y;	//.12f

		FIXED x,y;
		parent->getAbsolutePos(x,y);
		obj_set_pos(&obj, (particles[i].pos.x>>12) + x - 4 , (particles[i].pos.y>>12) + y - 4);

		pushSprite(&obj);
	}

	lifetime--;
}
