#ifndef _CAMERA_COMPONENT_H_
#define _CAMERA_COMPONENT_H_
#include "component.h"

class Camera : public Component<Camera>
{
public:
	void update();
};

#endif
