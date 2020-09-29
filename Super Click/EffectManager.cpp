#include "EffectManager.h"



EffectManager::EffectManager(ResourceManager *rm) {
	shakeAmount = 0;
	this->rm = rm;
	timerStart = 150;
	timer = timerStart;
	flashAmount = 0;
}


EffectManager::~EffectManager()
{
}

void EffectManager::Update() {
	for (unsigned i = 0; i < effects.size(); i++) {
		effects[i]->Update();
		if (effects[i]->GetEffectType() == LARGE_FIRE) {
			effects.push_back(unique_ptr<FireSmall>(new FireSmall(effects[i]->GetX(), effects[i]->GetY(), (rand() % 360) * (3.14159265358 / 180), 0)));
		}
		else if (effects[i]->GetEffectType() == EXPLOSION || effects[i]->GetEffectType() == FIRE || effects[i]->GetEffectType() == LARGE_FIRE) {
			if (effects[i]->GetEffectType() == EXPLOSION|| rand() % 10 == 0) {
				float distance = 0;
				while (rand() % 10 >= 1)
					distance++;
				float dir = (rand() % 360) * (3.14159265358 / 180);
				AddEffect(effects[i]->GetX() + cos(dir) * distance, effects[i]->GetY() + sin(dir) * distance, BURN);
			}
		}
	}

	for (unsigned i = 0; i < permEffects.size(); i++) {
		permEffects[i]->Update();

		if (permEffects[i]->GetEffectType() == CRACK && rand() % 10 == 0) {
			if (permEffects[i]->GetAttr() > 1) {
				int amount = 1;
				if (rand() % 2 == 0)
					amount = 2;
				for (int j = 0; j < amount; j++) {
					//permEffects.push_back(new Crack(permEffects[i]->GetX(), permEffects[i]->GetY(), permEffects[i]->GetDir() + .5, permEffects[i]->GetLiftStart(), 1));
					permEffects.push_back(unique_ptr<Crack> (new Crack(permEffects[i]->GetX(), permEffects[i]->GetY(), permEffects[i]->GetDir() + (rand() % 1000 - 500) * .0001, permEffects[i]->GetLife() * .9, permEffects[i]->GetAttr())));

				}
			}
		}
	}

	if (shakeAmount > 15)
		shakeAmount = 15;

	if (shakeAmount > 0 && rand() % 5 == 0)
			shakeAmount--;

	flashAmount *= .8;
}

void EffectManager::Draw() {
	for (auto &effect : effects)
		effect->Draw(rm);

	al_set_target_bitmap(rm->GetImage("effects"));

	for (auto &effect : permEffects)
		effect->Draw(rm);
}

void EffectManager::AddEffect(int x, int y, int type) {
	switch (type) {
	case NADA:
		effects.push_back(unique_ptr<Effect>(new Effect(x, y)));
		break;
	case FIRE:
		effects.push_back(unique_ptr<FireSmall>(new FireSmall(x, y, rand() % 360 * (3.14159265358 / 180))));
		break;
	case EXPLOSION:
		effects.push_back(unique_ptr<Explosion>(new Explosion(x, y, rm)));
		break;
	case LARGE_FIRE:
		effects.push_back(unique_ptr<FireBig>(new FireBig(x, y, rand() % 360 * (3.14159265358 / 180))));
		break;
	case CRACK:
		permEffects.push_back(unique_ptr<Crack>(new Crack(x, y, rand() % 360 * (3.14159265358 / 180), 20 + rand() % 10, 5)));
		break;
	case BURN:
		permEffects.push_back(unique_ptr<Burn>(new Burn(x, y, 2 + rand() % 4, 2)));
		break;
	}
}

void EffectManager::Cleanup() {
	
	for (unsigned i = 0; i < effects.size();) {
		if (effects[i]->GetActive())
			i++;
		else {
			if (effects[i]->GetEffectType() == LARGE_FIRE)
				AdditionalExplode(effects[i]->GetX(), effects[i]->GetY());

			effects.erase(effects.begin() + i);
		}
	}
	
	for (unsigned i = 0; i < permEffects.size();) {
		if (permEffects[i]->GetActive())
			i++;
		else {
			permEffects.erase(permEffects.begin() + i);
		}
	}
}

void EffectManager::AdditionalExplode(int x, int y) {
	rm->PlaySample(string("explosion" + to_string(rand() % 9 + 1)).c_str(), 1);

	for (int i = 0; i < 10; i++) {
		float distance = rand() % 100;
		float dir = (rand() % 360) * (3.14159265358 / 180);
		AddEffect(x + distance * cos(dir), y + distance * sin(dir), 2);
	}

	for (int i = 0; i < 100; i++) {
		AddEffect(x, y, 1);
	}

	shakeAmount += 10;
	flashAmount = .8;
}

void EffectManager::Explode(int x, int y) {
	int amount = 14 + rand() % 3;
	for (int i = 0; i < amount; i++)
		AddEffect(x, y, LARGE_FIRE);

	for (int i = 0; i < 20; i++) {
		float distance = rand() % 10;
		float dir = (rand() % 360) * (3.14159265358 / 180);
		AddEffect(x + cos(dir) * distance, y + sin(dir) * distance, CRACK);
	}

	AdditionalExplode(x, y);
}

void EffectManager::UpdateTimer() {
	if (timer > 0)
		timer--;
}

void EffectManager::ResetTimer() {
	timer = timerStart;
}

int EffectManager::GetShakeAmount()
{
	return shakeAmount;
}

int EffectManager::GetSize()
{
	return (int)effects.size();
}

int EffectManager::GetTimer()
{
	return timer;
}

float EffectManager::GetFlashAmount()
{
	return flashAmount;
}
