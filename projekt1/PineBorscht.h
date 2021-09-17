#pragma once
#include "Plant.h"
#include "Animal.h"
#include "Human.h"

class PineBorscht :public Plant {
public:
	PineBorscht(int x, int y, World* world);
	void newPlant(int x, int y) override;
	void action();
	bool specialEffect(Organism* attacker) override;
	string getName() override;
};