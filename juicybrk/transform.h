#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_
#include "types.h"

class Transform
{
protected:
	Transform* parent;

public:
	FIXED x,y;

	Transform();
	Transform(Transform* parent);
	~Transform();

	inline Transform* getParent() {
		return parent;
	}

	inline void setPosition(FIXED xpos, FIXED ypos) {
		x = xpos;
		y = ypos;
	}

	FIXED getAbsoluteX();
	FIXED getAbsoluteY();
	void getAbsolutePos(FIXED& xpos, FIXED& ypos);
};

#endif
