#pragma once
#include "Organism.h"
#include "Plant.h"
#include <Vector>
#include <string>

class Animal :public Organism {
public:
	Animal(int power, int initiative, int x, 
		int y, int age, char symbol, World* world);
	void action() override;
	void collision(Organism* other_org) override;
	void move(int destX, int destY);
	void battle(Organism* defender);
	void eatPlant(Organism* plant);
	virtual void newChild(int x, int y) = 0;
	virtual bool hasDefended(int enemyPower);
	virtual bool hasEscaped();
	virtual bool isHuman();
	virtual string getName() = 0;
};