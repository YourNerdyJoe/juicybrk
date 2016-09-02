#include "transform.h"

Transform::Transform() : parent(nullptr)
{
}

Transform::Transform(Transform* parent) : parent(parent)
{
}

Transform::~Transform()
{
}

FIXED Transform::getAbsoluteX()
{
	if(parent != nullptr)
		return x + parent->getAbsoluteX();
	else
		return x;
}

FIXED Transform::getAbsoluteY()
{
	if(parent != nullptr)
		return y + parent->getAbsoluteY();
	else
		return y;
}

void Transform::getAbsolutePos(FIXED& xpos, FIXED& ypos)
{
	if(parent == nullptr)
	{
		xpos = x;
		ypos = y;
	}
	else
	{
		parent->getAbsolutePos(xpos,ypos);
		xpos += x;
		ypos += y;
	}
}
