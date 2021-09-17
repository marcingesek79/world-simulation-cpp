#include "Guarana.h"

// Konstruktor
Guarana::Guarana(int x, int y, World* world):
	Plant(0, 0, x, y, 0, 'g', world){}

// Zasianie nowej rosliny
void Guarana::newPlant(int x, int y) {
	Guarana* guarana = new Guarana(x, y, world);
	world->getMatrix()[y][x] = guarana;
	world->getOrganisms()->push_back(guarana);
	string event = "Zasiano guarane [" + to_string(x) +
		", " + to_string(y) + "]";
	world->getEventHandler()->addEvent(event);
}

// Specjalny efekt - dodanie sily
bool Guarana::specialEffect(Organism* attacker) {
	int attackerPower = attacker->getPower();
	attacker->setPower(attackerPower + 3);
	string event = dynamic_cast<Animal*>(attacker)->getName()+ " +3 do sily";
	world->getEventHandler()->addEvent(event);
	return false;
}

// Zwraca nazwe
string Guarana::getName() {
	return "'Guarana'";
}