#include "Effect.h"




Effect::Effect(float x, float y) {
	this->x = x;
	this->y = y;
	this->life = 100 + rand() % 100;
	this->lifeStart = this->life;
	this->active = true;
}

Effect::~Effect()
{
}

void Effect::Update() {
	life--;
	if (life <= 0)
		active = false;
}

void Effect::Draw(ResourceManager *rm) {
	al_draw_filled_circle(x, y, 4, al_map_rgb(255, 0, 255));
}

int Effect::GetEffectType() {
	return 0;
}

float Effect::GetAttr()
{
	return 0.0f;
}

void Effect::SetPos(float x, float y) {
	this->x = x;
	this->y = y;

}

void Effect::SetActive(bool active) {
	this->active = active;
}

void Effect::SetLife(int life) {
	this->life = life;
}

void Effect::SetLifeStart(int a) {
	this->lifeStart = a;
}

float Effect::GetX()
{
	return x;
}

float Effect::GetY()
{
	return y;
}

float Effect::GetDir()
{
	return 0.0f;
}

bool Effect::GetActive()
{
	return active;
}

int Effect::GetLife()
{
	return life;
}

int Effect::GetLiftStart()
{
	return lifeStart;
}
