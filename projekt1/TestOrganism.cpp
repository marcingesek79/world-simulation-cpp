#include<iostream>
#include"TestOrganism.h"
using namespace std;

TestOrganism::TestOrganism(int power, int initiative, int x, int y, int age, World* world)
	:Organism(power, initiative, x, y, age, world) {}

void TestOrganism::draw() {
	cout << "#";
}