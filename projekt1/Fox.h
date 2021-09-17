#pragma once
#include "Animal.h"

class Fox :public Animal {
public:
	Fox(int x, int y, World* world);
	void newChild(int x, int y) override;
	void action();
	string getName() override;
};