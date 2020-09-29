#include "Explosion.h"


Explosion::Explosion(int x, int y, ResourceManager *rm) : Effect(x, y) {
	this->frame = 0 -rand() % 10;
	this->timerStart = 2;
	this->timer = this->timerStart;
	this->maxFrame = 8;
	this->scale = 1;
	this->rm = rm;
}

Explosion::~Explosion() {
	printf("deleted explosion");
}

void Explosion::Update() {
	timer--;

	if (timer <= 0) {
		timer = timerStart;

		frame++;

		//if (frame == 0)
			//rm->PlaySample("hit", 1);
		if (frame > maxFrame)
			SetActive(false);
	}
}

void Explosion::Draw(ResourceManager *rm){
	ALLEGRO_BITMAP *tmp = rm->GetImage("explosion");
	al_draw_bitmap_region(tmp, 128 * frame, 0, 128, 128, GetX() - 128 / 2, GetY() - 128 / 2, NULL);
}

int Explosion::GetEffectType()
{
	return 2;
}
