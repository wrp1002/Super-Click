#include "Crack.h"



Crack::Crack(float x, float y, float dir, int life, float thickness) : Effect(x, y) {
	this->dir = dir;
	this->thickness = thickness;
	speed = 8;
	moving = true;
	SetLife(life);
	SetLifeStart(life);
	prevX = x;
	prevY = y;
	startDir = dir;

	timerStart = 2;
	timer = timerStart;
}

Crack::~Crack() {


}

void Crack::Update() {
	if (moving) {
		Effect::Update();

		prevX = x;
		prevY = y;

		if (GetLife() <= 0) {
			moving = false;
		}

		timer--;
		if (timer <= 0) {
			timer = timerStart;
			dir = startDir + (rand() % 2000 - 1000) * .001;
			//speed -= .5;
		}

		if (thickness > 1)
			thickness -= .25;

		int x = GetX() + cos(dir) * speed;
		int y = GetY() + sin(dir) * speed;

		SetPos(x, y);

		
	}
}

void Crack::Draw(ResourceManager *rm) {
	float color = 0;
	al_draw_filled_circle(GetX(), GetY(), thickness / 2, al_map_rgba_f(color, color, color, .8));

/*	if (thickness < 5) {
		al_draw_line(GetX(), GetY(), prevX, prevY, al_map_rgb(100, 100, 100), thickness + 1);
		al_draw_line(GetX(), GetY(), prevX, prevY, al_map_rgb(50, 50, 50), thickness);
	}*/
	
	al_draw_line(GetX(), GetY(), prevX, prevY, al_map_rgba_f(color, color, color, .8), thickness);
}

int Crack::GetEffectType() {
	return 4;
}

float Crack::GetAttr()
{
	return thickness;
}

float Crack::GetDir()
{
	return dir;
}

float Crack::GetThickness()
{
	return thickness;
}
