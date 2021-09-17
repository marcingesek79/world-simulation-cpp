#pragma once
#include "Organism.h"
#include<Vector>
#include<string>

class Plant :public Organism {
public:
	Plant(int power, int initiative, int x,
		int y, int age, char symbol, World* world);
	void action() override;
	void collision(Organism* other_org) override;
	virtual bool specialEffect(Organism* attacker);
	virtual void newPlant(int x, int y) = 0;
	virtual string getName() = 0;
};