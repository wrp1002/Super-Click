#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <Windows.h>

#include "ResourceManager.h"

class Mouse
{
private:
	ALLEGRO_BITMAP * img;
	
	float height;
	float vel;
	bool active;
	bool hit;

public:
	POINT pos;
	Mouse();
	~Mouse();

	POINT *GetPos();
	void Draw(ALLEGRO_BITMAP *img);
	void Update(ResourceManager * rm);
	void Fall(int x, int y, ResourceManager * rm);

	void SetActive(bool active);

	bool GetHit();
	bool GetActive();
};

