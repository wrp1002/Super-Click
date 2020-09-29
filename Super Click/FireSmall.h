#pragma once

#define _USE_MATH_DEFINES
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <math.h>

#include "Effect.h"
#include "ResourceManager.h"

class FireSmall : public Effect
{
private:
	

public:
	float drawDir;
	float dir;
	float speed;
	int type;


	FireSmall(int x, int y, float dir, int type = -1);
	~FireSmall();

	virtual void Update();
	virtual void Draw(ResourceManager *rm);
	virtual int GetEffectType();
};

