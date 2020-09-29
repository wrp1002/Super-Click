#include "Burn.h"



Burn::Burn(int x, int y, int r, int life) : Effect(x, y) {
	this->r = r;
	SetLife(life);
}

Burn::~Burn()
{
}

void Burn::Draw(ResourceManager *rm) {
	for (int i = 0; i < 3; i++)
		al_draw_filled_circle(x + rand() % 11 -5 , y + rand() % 11 - 5, r + rand() % 5, al_map_rgba_f(0, 0, 0, .05));
}

int Burn::GetEffectType() {
	return 5;
}
