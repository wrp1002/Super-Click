#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class Object
{
public:
	ALLEGRO_BITMAP * img;
	Object();
	~Object();
};

