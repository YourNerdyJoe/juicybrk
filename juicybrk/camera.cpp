#include "camera.h"
#include "video.h"
#include "object.h"

void Camera::update()
{
	FIXED x,y;
	parent->getAbsolutePos(x, y);

	REG_BG0HOFS = -x;
	REG_BG0VOFS = -y;
}
