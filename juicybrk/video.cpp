#include "video.h"

/* Initialize Video Mode */
void videoInit()
{
	REG_DISPCNT = (DCNT_MODE0|DCNT_BG0|DCNT_OBJ|DCNT_OBJ_1D);
	REG_BG0CNT = BG_4BPP|BG_REG_32x32|BG_CBB(0)|BG_SBB(8);
}

/* Manage Sprites in  OAM */

static int spr_stack_pos = 0;

void resetSpriteStack()
{
	spr_stack_pos = 0;
}

void pushSprite(OBJ_ATTR* oam_obj)
{
	if(spr_stack_pos < MAX_SPRITES)	//add debug later
		obj_copy(&oam_mem[spr_stack_pos++], oam_obj, 1);
}

void hideUnusedSprites()
{
	for(; spr_stack_pos < MAX_SPRITES; spr_stack_pos++)
	{
		obj_hide(&oam_mem[spr_stack_pos]);
	}
}
