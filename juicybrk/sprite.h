#ifndef _SPRITE_COMPONENT_H_
#define _SPRITE_COMPONENT_H_
#include "component.h"
#include <tonc.h>

class Sprite : public Component<Sprite>
{
	OBJ_ATTR oam_obj;
	
public:
	POINT anchor;
	bool active;

	Sprite();
	~Sprite();

	void update();

	inline void setAnchor(int x, int y) {
		anchor = {x, y};
	}
	inline void setAttributes(u16 attr0, u16 attr1, u16 attr2) {
		obj_set_attr(&oam_obj, attr0, attr1, attr2);
	}

	inline int getWidth() {
		return obj_get_width(&oam_obj);
	}
	inline int getHeight() {
		return obj_get_height(&oam_obj);
	}
	inline void getSize(int& w, int& h) {
		const u8* sz = obj_get_size(&oam_obj);
		w = (int)sz[0];
		h = (int)sz[1];
	}
};

#endif
