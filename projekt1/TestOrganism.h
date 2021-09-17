#pragma once
#include<iostream>
#include "Organism.h"
using namespace std;

class TestOrganism :public Organism {
public:
	TestOrganism(int power, int initiative, int x, int y,
		int age, World* world);
	void draw() override;
};