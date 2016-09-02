#ifndef _PARTICLES_COMPONENT_H_
#define _PARTICLES_COMPONENT_H_
#include "component.h"
extern "C" {
#include <tonc_math.h>
}

class Particles : public Component<Particles>
{
	struct Particle {
		POINT pos;
		POINT speed;
	}*particles;
	uint max_particles;
	FIXED direction, direction_range;
	FIXED max_speed;
	int lifetime;
	OBJ_ATTR obj;
public:
	Particles();
	~Particles();

	void startParticles(uint num_p, FIXED dir, FIXED dir_range, FIXED max_spd, int life, OBJ_ATTR oam_obj);

	void update();
};

#endif
