#include "Wolf.h"

// Konstruktor
Wolf::Wolf(int x, int y, World* world) : 
	Animal(9, 5, x, y, 0, 'W', world){}

// Rozmnazanie sie
void Wolf::newChild(int x, int y) {
	Wolf* wolf = new Wolf(x, y, world);
	world->getMatrix()[y][x] = wolf;
	world->getOrganisms()->push_back(wolf);
	string event = "Narodzil sie wilk [" + to_string(x) + 
		", " + to_string(y) + "]";
	world->getEventHandler()->addEvent(event);
}

// Zwraca nazwe
string Wolf::getName() {
	return "'Wilk'";
}
