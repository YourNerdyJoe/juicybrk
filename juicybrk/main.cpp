#include <tonc.h>
#include "filesystem.h"
#include "video.h"
#include "component.h"
#include "object.h"
#include "sprite.h"
#include "physics.h"
#include "playerinputsystem.h"
#include "ballsystem.h"
#include "bricks.h"
#include <string.h>
#include "gbfs.h"
#include "particles.h"
#include "camera.h"
#include "rumble.h"

u8 __rom_end__;

int main(int argc, char* argv[])
{
	//Systems
	System<Sprite> spr_sys;
	System<Physics> phys_sys;
	PlayerInputSystem input_sys;
	BallSystem ball_sys;
	System<Particles> particle_sys;
	System<Camera> cam_sys;
	RumbleSystem rumble_sys;

	Sprite::registerSystem(&spr_sys);
	Physics::registerSystem(&phys_sys);
	Particles::registerSystem(&particle_sys);
	Camera::registerSystem(&cam_sys);
	Rumble::registerSystem(&rumble_sys);

	//camera
	Object cam;
	cam.addComponent<Camera>();
	cam.addComponent<Rumble>();

	//player
	Object player(&cam);
	player.setPosition(120, 140);

	auto pl_spr = player.addComponent<Sprite>();
	pl_spr->setAttributes(ATTR0_WIDE, ATTR1_SIZE_32x16, 0|(2<<12));
	pl_spr->setAnchor(16, 8);

	auto pl_phys = player.addComponent<Physics>();
	pl_phys->setCollider(-16, -8, 16, 8);
	input_sys.addComponent(pl_phys);

	//ball
	Object ball(&cam);
	ball.setPosition(100, 100);

	auto bl_spr = ball.addComponent<Sprite>();
	bl_spr->setAttributes(ATTR0_SQUARE, ATTR1_SIZE_8x8, 0|(3<<12));
	bl_spr->setAnchor(4, 4);

	auto bl_phys = ball.addComponent<Physics>();
	bl_phys->setCollider(-4, -4, 4, 4);
	bl_phys->xspeed = 2;
	bl_phys->yspeed = 2;
	ball_sys.addComponent(bl_phys);

	//bricks
	initializeBricks();

	//Initialize
	videoInit();

	irq_init(nullptr);
	irq_add(II_VBLANK,nullptr);

	FileSystem::openFS((u8*)find_first_gbfs_file((void*)0x8016000));

	const void* data = FileSystem::openFile("brick.pal.bin");
	if(data!=nullptr)
	{
		LZ77UnCompVram(data,pal_bg_mem);
		for(int i=1;i<=4;i++)
		{
			memcpy(pal_bg_bank[i],pal_bg_bank[0],32);
			for(int j=0;j<16;j++)
			{
				//make bricks red
				pal_bg_bank[i-1][j] &= RED_MASK;
				pal_bg_bank[i-1][j] -= (i-1)*(pal_bg_bank[0][j]>>3);	//reduce by 1/8
			}
		}
	}
	else
	{
		pal_bg_mem[1] = RGB15(31,31,31);
		pal_bg_mem[2] = RGB15(31,0,0);

		*(u8**)pal_bg_mem = &__rom_end__;
	}

	data = FileSystem::openFile("brick.img.bin");
	LZ77UnCompVram(data,&tile_mem[0][1]);

	//test//
	//memset16(&tile_mem[0][1],0x1111,16);
	//memset16(&tile_mem[0][2],0x2222,16);

	//pal_bg_mem[1] = RGB15(31,31,31);
	//pal_bg_mem[2] = RGB15(31,0,0);

	//memset16(&se_mem[8],1,16);

	memset16(&tile_mem_obj[0][0],0x1111,16*8);
	pal_obj_mem[1] = RGB15(31,31,31);
	pal_obj_bank[1][1] = RGB15(31,16,0);	//particle color
	pal_obj_bank[2][1] = RGB15(31,10,10);	//paddle color
	pal_obj_bank[3][1] = RGB15(31,16,10);	//ball color
	pal_obj_bank[4][1] = RGB15(31,0,12);	//particle from paddle color

	data = FileSystem::openFile("particle.img.bin");
	LZ77UnCompVram(data,&tile_mem_obj[0][8]);
	////////

	//main loop
	while(1)
	{
		//input
		key_poll();
		input_sys.update();
		//reset
		if(key_hit(KEY_START)) {
			initializeBricks();
		}

		//update
		phys_sys.update();
		ball_sys.update();
		rumble_sys.update();
		cam_sys.update();

		//sprites
		resetSpriteStack();
		spr_sys.update();
		particle_sys.update();
		hideUnusedSprites();

		drawBricks();

		//garbage collection
		spr_sys.garbageCollection();
		phys_sys.garbageCollection();
		particle_sys.garbageCollection();

		VBlankIntrWait();
	}

	return 0;
}
