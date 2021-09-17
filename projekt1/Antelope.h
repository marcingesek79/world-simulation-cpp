#pragma once
#include "Animal.h"

class Antelope :public Animal {
public:
	Antelope(int x, int y, World* world);
	void newChild(int x, int y) override;
	void action();
	bool hasEscaped() override;
	string getName() override;
};