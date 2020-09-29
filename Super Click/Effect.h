#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "ResourceManager.h"


class Effect
{
private:
	
	float type;
	int life, lifeStart;
	bool active;

public:
	float x, y;

	Effect(float x, float y);
	~Effect();

	virtual void Update();
	virtual void Draw(ResourceManager *rm);
	virtual int GetEffectType();
	virtual float GetAttr();
	
	void SetPos(float x, float y);
	void SetActive(bool active);
	void SetLife(int life);
	void SetLifeStart(int a);

	virtual float GetX();
	virtual float GetY();
	virtual float GetDir();
	bool GetActive();
	int GetLife();
	int GetLiftStart();
};

