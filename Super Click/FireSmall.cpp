#include "FireSmall.h"




FireSmall::FireSmall(int x, int y, float dir, int type) : Effect(x, y) {
	drawDir = rand() % 360 * (M_PI / 180);
	this->dir = dir;
	this->speed = rand() % 10000 * .001;
	//SetLife(200 + rand() % 100);

	if (type == -1) {
		this->type = rand() % 4;
	}
	else {
		this->type = type;
		this->speed = rand() % 100 * .001;
	}
}

FireSmall::~FireSmall()
{
}

void FireSmall::Update() {
	Effect::Update();
	Effect::Update();

	float newX = GetX() + speed * cos(dir) +rand() % 5 - 2;
	float newY = GetY() + speed * sin(dir) +rand() % 5 - 2;
	SetPos(newX, newY);

	float tmp = dir;
	drawDir += (rand() % 1000 - 500) * .001;
	dir += cos(GetLife()) * .01;

	if (speed > 1)
		speed *= .94;
}

void FireSmall::Draw(ResourceManager *rm) {
	float scale = float(GetLife()) / 100;

	ALLEGRO_BITMAP *tmp = NULL;
	if (type == 0)
		tmp = rm->GetImage("fire");
	else if (type == 1)
		tmp = rm->GetImage("smoke");
	else if (type == 2)
		tmp = rm->GetImage("smoke2");
	else if (type == 3)
		tmp = rm->GetImage("fireBig");

	//al_draw_rotated_bitmap(tmp, al_get_bitmap_width(tmp) / 2, al_get_bitmap_height(tmp) / 2, GetX(), GetY(), drawDir, NULL);
	al_draw_scaled_rotated_bitmap(tmp, al_get_bitmap_width(tmp) / 2, al_get_bitmap_height(tmp) / 2, GetX(), GetY(), scale, scale, rand() % 360 * (3.14159265358 / 180), NULL);
}

int FireSmall::GetEffectType()
{
	return 1;
}
