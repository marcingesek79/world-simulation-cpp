#include"WolfBerries.h"

// Konstruktor
WolfBerries::WolfBerries(int x, int y, World* world):
	Plant(99, 0, x, y, 0, 'x', world){}

// Zasianie nowej rosliny
void WolfBerries::newPlant(int x, int y) {
	WolfBerries* wolfBerries = new WolfBerries(x, y, world);
	world->getMatrix()[y][x] = wolfBerries;
	world->getOrganisms()->push_back(wolfBerries);
	string event = "Zasiano wilcze jagody [" + to_string(x) +
		", " + to_string(y) + "]";
	world->getEventHandler()->addEvent(event);
}

// Specjalny efekt
bool WolfBerries::specialEffect(Organism* attacker) {
	if (dynamic_cast<Animal*>(attacker)->isHuman()) {
		world->setIsHumanAlive(false);
	}
	world->makeOrganismInactive(this);
	world->getMatrix()[y][x] = nullptr;
	int attX = attacker->getX();
	int attY = attacker->getY();
	world->makeOrganismInactive(attacker);
	world->getMatrix()[attY][attX] = nullptr;
	string event = dynamic_cast<Animal*>(attacker)->getName() +
		" zjadl " + getName() + " - oba organizmy umieraja";
	world->getEventHandler()->addEvent(event);
	return true;
}

// Zwraca nazwe
string WolfBerries::getName() {
	return "'Wilcze jagody'";
}