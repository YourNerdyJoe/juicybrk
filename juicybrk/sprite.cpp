#include "sprite.h"
#include "object.h"
#include "video.h"

Sprite::Sprite() : Component<Sprite>(), anchor({0,0}), active(true)
{
	memset16(&oam_obj,0,3);
}

Sprite::~Sprite()
{
}

void Sprite::update()
{
	if(active)
	{
		FIXED x,y;
		parent->getAbsolutePos(x,y);
		obj_set_pos(&oam_obj, x-anchor.x, y-anchor.y);

		pushSprite(&oam_obj);
	}
}
