#pragma once
#include "Animal.h"

class Turtle :public Animal {
public:
	Turtle(int x, int y, World* world);
	void newChild(int x, int y) override;
	void action();
	bool hasDefended(int enemyPower) override;
	string getName() override;
};