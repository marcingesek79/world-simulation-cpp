#pragma once
#include "Plant.h"
#include "Animal.h"

class WolfBerries : public Plant {
public:
	WolfBerries(int x, int y, World* world);
	void newPlant(int x, int y) override;
	bool specialEffect(Organism* attacker) override;
	string getName() override;
};