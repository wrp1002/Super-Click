#include "Mouse.h"



Mouse::Mouse() {
	this->pos.x = 0;
	this->pos.y = 0;
	this->height = 1;
	this->active = false;
	this->hit = false;
}


Mouse::~Mouse() {
}

POINT *Mouse::GetPos()
{
	return &this->pos;
}

void Mouse::Draw(ALLEGRO_BITMAP *img) {
	if (active) {
		int w = al_get_bitmap_width(img);
		int h = al_get_bitmap_height(img);
		//al_draw_bitmap(img, pos.x, pos.y, NULL);
		al_draw_scaled_bitmap(img, 0, 0, w, h, pos.x - w * height / 2, pos.y - h * height / 2, w * height, h * height, NULL);
	}
}

void Mouse::Update(ResourceManager * rm) {
	if (active) {
		this->vel += .0004;
		if (vel > .04)
			vel = .04;
		this->height -= this->vel;
		if (height < .04 && !hit) {
			height = .04;
			hit = true;
			rm->PlaySample("hit", 1);
		}
	}
}

void Mouse::Fall(int x, int y, ResourceManager * rm) {
	int w =775;
	int h =775;
	this->pos.x = x + 4;
	this->pos.y = y + 9;
	this->height = 4;
	this->vel = 0;
	this->hit = false;
	this->active = true;

	rm->PlaySample("falling", 1);
}

void Mouse::SetActive(bool active) {
	this->active = active;
}

bool Mouse::GetHit()
{
	return hit;
}

bool Mouse::GetActive()
{
	return active;
}
