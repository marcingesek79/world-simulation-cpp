#pragma once
#include "Animal.h"

class Sheep :public Animal {
public:
	Sheep(int x, int y, World* world);
	void newChild(int x, int y) override;
	string getName() override;
};