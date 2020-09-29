#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "ResourceManager.h"
#include "Effect.h"
#include "FireSmall.h"

class FireBig : public FireSmall
{
public:
	FireBig(float x, float y, float dir);
	~FireBig();

	void Update();
	void Draw(ResourceManager *rm);
	int GetEffectType();
};

