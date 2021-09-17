#pragma once
#include "Animal.h"

class Wolf : public Animal {
public:
	Wolf(int x, int y, World* world);
	void newChild(int x, int y) override;
	string getName() override;
};