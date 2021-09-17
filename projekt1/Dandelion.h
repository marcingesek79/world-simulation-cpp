#pragma once
#include "Plant.h"

class Dandelion :public Plant {
public:
	Dandelion(int x, int y, World* world);
	void newPlant(int x, int y) override;
	void action();
	string getName() override;
};