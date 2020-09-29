#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

#include "ResourceManager.h"
#include "Effect.h"

class Crack : public Effect
{
private:
	float prevX, prevY;
	float dir, speed, startDir;
	float thickness;
	int timer, timerStart;
	bool moving;

public:
	Crack(float x, float y, float dir, int life, float thickness);
	~Crack();


	void Update();
	void Draw(ResourceManager *rm);
	int GetEffectType();
	float GetAttr();

	float GetDir();
	float GetThickness();
};

