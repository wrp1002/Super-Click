#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "Effect.h"

class Burn : public Effect
{
private:
	float r;

public:
	Burn(int x, int y, int r, int life);
	~Burn();

	void Draw(ResourceManager *rm);
	int GetEffectType();
};

