#include "collision.h"

bool checkCollision(RECT& r1, RECT& r2)
{
	bool x = false, y = false;

	if( (r1.left < r2.right && r1.left > r2.left) ||
		(r1.right < r2.right && r1.right > r2.left))
	{
		x = true;
	}
	
	if( (r1.top < r2.bottom && r1.top > r2.top) ||
		(r1.bottom < r2.bottom && r1.bottom > r2.top))
	{
		y = true;
	}

	return x && y;
}
