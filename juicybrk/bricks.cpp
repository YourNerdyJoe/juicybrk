#include "bricks.h"
#include "video.h"

u8 bricks_alive[MAX_BRICKS];

void initializeBricks()
{
	int i;
	for(i = 0; i < MAX_BRICKS; i++)
	{
		bricks_alive[i] = 1;
	}
}

void drawBricks()
{
	int x,y;
	for(y = 0; y < BRICKS_VERTICAL; y++)
	{
		int tiley = y + BRICKS_TILEY_START;

		for(x = 0; x < BRICKS_HORIZONTAL; x++)
		{
			int tilex = x*2 + BRICKS_TILEX_START;
			
			int tilenum = tilex + tiley*SCREEN_TILE_WIDTH;

			int b = bricks_alive[x+y*BRICKS_HORIZONTAL];
			int pal = 3 - (y>>1);
			se_mem[SBB][tilenum] = b | (pal<<SE_PALBANK_SHIFT);
			se_mem[SBB][tilenum+1] = b*2 | (pal<<SE_PALBANK_SHIFT);
		}
	}
}

void getBrickCollider(int bx, int by, RECT& collider)
{
	int x,y;
	x = bx * 16 + BRICKS_TILEX_START * 8;
	y = (by + BRICKS_TILEY_START) * 8;

	collider = { x, y, x+16, y+8 };
}
