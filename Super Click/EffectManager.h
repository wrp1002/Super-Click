#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <vector>
#include <iostream>
#include <string>

#include "ResourceManager.h"
#include "Effect.h"
#include "FireSmall.h"
#include "Explosion.h"
#include "FireBig.h"
#include "Crack.h"
#include "Burn.h"

using namespace std;

enum EFFECT_TYPE { NADA, FIRE, EXPLOSION, LARGE_FIRE, CRACK, BURN };

class EffectManager
{
private:
	vector<unique_ptr<Effect>> effects;
	vector<unique_ptr<Effect>> permEffects;
	int shakeAmount;
	ResourceManager *rm;
	int timer, timerStart;
	float flashAmount;

	void AdditionalExplode(int x, int y);

public:
	EffectManager(ResourceManager *rm);
	~EffectManager();

	void Update();
	void Draw();
	void AddEffect(int x, int y, int type = 0);
	void Cleanup();
	void Explode(int x, int y);
	void UpdateTimer();
	void ResetTimer();

	int GetShakeAmount();
	int GetSize();
	int GetTimer();
	float GetFlashAmount();
};

