#include "PineBorscht.h"

// Konstruktor
PineBorscht::PineBorscht(int x, int y, World* world):
	Plant(10, 0, x, y, 0, 'b', world) {}

// Zasianie nowej rosliny
void PineBorscht::newPlant(int x, int y) {
	PineBorscht* pineBorscht = new PineBorscht(x, y, world);
	world->getMatrix()[y][x] = pineBorscht;
	world->getOrganisms()->push_back(pineBorscht);
	string event = "Zasiano barszcz sosn. [" + to_string(x) +
		", " + to_string(y) + "]";
	world->getEventHandler()->addEvent(event);
}

// Specjalny efekt
bool PineBorscht::specialEffect(Organism* attacker) {
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
 
// Wykonanie akcji  - zabicie wszystkiego dookola
void PineBorscht::action() {
	int randomNumber = world->randomNumber(1, 100);
	if (randomNumber > 90) {
		vector<vector<int>> possibleSpaces = world->possibleSpacesAround(x, y);
		if (possibleSpaces.size() > 0) {
			vector<int> chosenSpace = world->getRandomPossibleSpace(possibleSpaces);
			int destX = chosenSpace[0];
			int destY = chosenSpace[1];
			newPlant(destX, destY);
		}
	}
	vector<vector<int>> spacesWithOrganisms = world->spacesWithOrganismsAround(x, y);
	if (spacesWithOrganisms.size() <= 0) return;
	for (int i = 0; i < spacesWithOrganisms.size(); i++)
	{
		int eX = spacesWithOrganisms[i][0];
		int eY = spacesWithOrganisms[i][1];
		if (dynamic_cast<Human*>(world->getMatrix()[eY][eX])) {
			if (dynamic_cast<Human*>(world->getMatrix()[eY][eX])->getIsPowerActivated()) {
				continue;
			}
		}
		if (dynamic_cast<Animal*>(world->getMatrix()[eY][eX])) {
			string event = getName() +
				" zatrul " + dynamic_cast<Animal*>(world->getMatrix()[eY][eX])->getName();
			world->getEventHandler()->addEvent(event);
			if (dynamic_cast<Animal*>(world->getMatrix()[eY][eX])->isHuman()) {
				world->setIsHumanAlive(false);
			}
			world->makeOrganismInactive(world->getMatrix()[eY][eX]);
			world->getMatrix()[eY][eX] = nullptr;
		}
	}
}

// Zwraca nazwe
string PineBorscht::getName() {
	return "'Barszcz sosn.'";
}