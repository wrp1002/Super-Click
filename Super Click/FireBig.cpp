#include "FireBig.h"




FireBig::FireBig(float x, float y, float dir) : FireSmall(x, y, dir) {
	this->speed = rand() % 10000 * .001 + 4;
	SetLife(50 + rand() % 150);
}

FireBig::~FireBig()
{
}

void FireBig::Update() {
	FireSmall::Update();
	dir += cos(GetLife()) * .02;
	

}

void FireBig::Draw(ResourceManager *rm) {
	float scale = 1;
	ALLEGRO_BITMAP *tmp = rm->GetImage("fireBig");

	//al_draw_rotated_bitmap(tmp, al_get_bitmap_width(tmp) / 2, al_get_bitmap_height(tmp) / 2, GetX(), GetY(), drawDir, NULL);
	al_draw_scaled_rotated_bitmap(tmp, al_get_bitmap_width(tmp) / 2, al_get_bitmap_height(tmp) / 2, GetX(), GetY(), scale, scale, rand() % 360 * (3.14159265358 / 180), NULL);
}

int FireBig::GetEffectType()
{
	return 3;
}
