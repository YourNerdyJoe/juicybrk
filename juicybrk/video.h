#ifndef _VIDEO_H_
#define _VIDEO_H_
#include <tonc.h>

#define MAX_SPRITES 128

#define SCREEN_LEFT	0
#define SCREEN_TOP	0
#define SCREEN_RIGHT	240
#define SCREEN_BOTTOM	160

#define CBB 0
#define SBB 8

#define SCREEN_TILE_WIDTH 32
#define SCREEN_TILE_HEIGHT 32

void videoInit();

void resetSpriteStack();
void pushSprite(OBJ_ATTR* oam_obj);
void hideUnusedSprites();

#endif
