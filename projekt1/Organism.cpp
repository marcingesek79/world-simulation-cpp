#include<iostream>
#include "Organism.h"
using namespace std;

// Konstruktor
Organism::Organism(int power, int ini, int x, int y, 
	int age, char symbol, World* world) {
	this->power = power;
	this->initiative = ini;
	this->x = x;
	this->y = y;
	this->age = age;
	this->symbol = symbol;
	this->world = world;
}

void Organism::draw() {
	cout << symbol;
}

void Organism::makeOlder() {
	age++;
}

void Organism::setX(int x) {
	this->x = x;
}

int Organism::getX() {
	return x;
}

void Organism::setY(int y) {
	this->y = y;
}

int Organism::getY() {
	return y;
}

void Organism::setInitiative(int init) {
	initiative = init;
}

int Organism::getInitiative() {
	return initiative;
}

void Organism::setAge(int age) {
	this->age = age;
}
	
int Organism::getAge() {
	return age;
}

void Organism::setPower(int power) {
	this->power = power;
}

int Organism::getPower() {
	return power;
}

char Organism::getSymbol() {
	return symbol;
}
