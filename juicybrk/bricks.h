#ifndef _BRICKS_H_
#define _BRICKS_H_
#include "types.h"
extern "C" {
#include <tonc_math.h>
}

#define BRICKS_HORIZONTAL 10
#define BRICKS_VERTICAL 8

#define MAX_BRICKS (BRICKS_HORIZONTAL*BRICKS_VERTICAL)

#define BRICKS_TILEX_START 5
#define BRICKS_TILEY_START 2

extern u8 bricks_alive[MAX_BRICKS];

void initializeBricks();
void drawBricks();
void getBrickCollider(int bx, int by, RECT& collider);

#endif
