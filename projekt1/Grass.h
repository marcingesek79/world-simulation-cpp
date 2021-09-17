#pragma once
#include "Plant.h"

class Grass : public Plant {
public:
	Grass(int x, int y, World* world);
	void newPlant(int x, int y) override;
	string getName() override;
};