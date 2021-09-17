#include"Grass.h"

// Konstruktor
Grass::Grass(int x, int y, World* world):
	Plant(0, 0, x, y, 0, 't', world){}

// Zasianie nowej rosliny
void Grass::newPlant(int x, int y) {
	Grass* grass = new Grass(x, y, world);
	world->getMatrix()[y][x] = grass;
	world->getOrganisms()->push_back(grass);
	string event = "Zasiano trawe [" + to_string(x) +
		", " + to_string(y) + "]";
	world->getEventHandler()->addEvent(event);
}

// Zwraca nazwe
string Grass::getName() {
	return "'Trawa'";
}