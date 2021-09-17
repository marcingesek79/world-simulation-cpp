#include "Sheep.h"

// Konstruktor
Sheep::Sheep(int x, int y, World* world) :
	Animal(4, 4, x, y, 0, 'S', world){}

// Rozmnazanie sie
void Sheep::newChild(int x, int y) {
	Sheep* sheep = new Sheep(x, y, world);
	world->getMatrix()[y][x] = sheep;
	world->getOrganisms()->push_back(sheep);
	string event = "Narodzila sie owca [" + to_string(x) +
		", " + to_string(y) + "]";
	world->getEventHandler()->addEvent(event);
}

// Zwraca nazwe
string Sheep::getName() {
	return "'Owca'";
}
