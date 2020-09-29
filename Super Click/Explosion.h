#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "ResourceManager.h"
#include "Effect.h"

class Explosion : public Effect
{
private:
	int frame;
	int timer, timerStart;
	int maxFrame;
	float scale;
	ResourceManager *rm;

public:
	Explosion(int x, int y, ResourceManager *rm);
	~Explosion();

	void Update();
	void Draw(ResourceManager *rm);
	int GetEffectType();
};

