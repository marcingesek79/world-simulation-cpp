#pragma once
#include<iostream>
#include<algorithm>
#include"World.h"
using namespace std;

class World;

class Organism { 
protected:
	int power;
	int initiative;
	int x;
	int y;
	int age;
	char symbol;
	World* world;
public:
	Organism(int power, int initiative, int x, int y, int age, char symbol, World* world);
	virtual void action() = 0;
	virtual void collision(Organism* other_org) = 0;
	void draw();
	void makeOlder();
	// Gettery & settery
	void setX(int x);
	int getX();
	void setY(int y);
	int getY();
	void setInitiative(int init);
	int getInitiative();
	void setAge(int age);
	int getAge();
	void setPower(int power);
	int getPower();
	char getSymbol();
};