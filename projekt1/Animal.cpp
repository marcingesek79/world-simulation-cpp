#include "Animal.h"

// Konstruktor
Animal::Animal(int power, int initiative, int x,
	int y, int age, char symbol, World* world) :
	Organism(power, initiative, x, y, age, symbol, world) {};

// Wykonywanie akcji
void Animal::action() {
	vector<vector<int>> possibleSpaces = world->possibleSpacesToWalk(x, y);
	vector<int> chosenSpace = world->getRandomPossibleSpace(possibleSpaces);
	int destX = chosenSpace[0];
	int destY = chosenSpace[1];
	if (world->getMatrix()[destY][destX] == nullptr) {
		move(destX, destY);
	}
	else {
		Organism* other_org = world->getMatrix()[destY][destX];
		collision(other_org);
	}
}

// Event kolizji
void Animal::collision(Organism* other_org) {
	if (other_org->getSymbol() == symbol) {
		vector<vector<int>> possibleSpaces = world->possibleSpacesAround(other_org->getX(), other_org->getY());
		if (possibleSpaces.size() <= 0) {
			world->getEventHandler()->addEvent("Brak wolnego pola");
			return;
		}
		vector<int> cell = world->getRandomPossibleSpace(possibleSpaces);
		newChild(cell[0], cell[1]);
	}
	else {
		if (dynamic_cast<Animal*>(other_org)) {
			battle(other_org);
		}
		else if (dynamic_cast<Plant*>(other_org)) {
			eatPlant(other_org);
		}
	}
}

// Poruszanie sie
void Animal::move(int destX, int destY) {
	world->getMatrix()[destY][destX] = this;
	world->getMatrix()[y][x] = nullptr;
	y = destY;
	x = destX;
}

// Walka z innym zwierzeciem
void Animal::battle(Organism* defender) {
	int dX = defender->getX();
	int dY = defender->getY();
	if (dynamic_cast<Animal*>(defender)->hasDefended(power)) return;
	if (dynamic_cast<Animal*>(defender)->hasEscaped()) {
		move(dX, dY);
		return;
	}
	if (power >= defender->getPower()) {
		if (dynamic_cast<Animal*>(defender)->isHuman()) {
			world->setIsHumanAlive(false);
		}
		world->makeOrganismInactive(defender);
		world->getMatrix()[dY][dX] = nullptr;
		
		move(dX, dY);
		string event = getName() + " pokonuje " + dynamic_cast<Animal*>(defender)->getName();
		world->getEventHandler()->addEvent(event);
	}
	else {
		if (dynamic_cast<Animal*>(this)->isHuman()) {
			world->setIsHumanAlive(false);
		}
		world->makeOrganismInactive(this);
		world->getMatrix()[y][x] = nullptr;
		string event = dynamic_cast<Animal*>(defender)->getName() + " pokonuje " + getName();
		world->getEventHandler()->addEvent(event);
	}
}

// Zjedzenie rosliny
void Animal::eatPlant(Organism* plant) {
	int pX = plant->getX();
	int pY = plant->getY();
	cout << "my x:" << x << "my y: " << y << endl;
	bool isEventAdded = false;
	if (dynamic_cast<Plant*>(plant)->specialEffect(this)) {
		isEventAdded = true;
		return;
	}
	world->makeOrganismInactive(plant);
	world->getMatrix()[pY][pX] = nullptr;
	move(pX, pY);
	if (!isEventAdded) {
		string event = getName() + " zjada " + dynamic_cast<Plant*>(plant)->getName();
		world->getEventHandler()->addEvent(event);
	}
}

bool Animal::hasDefended(int enemyPower) {
	return false;
}

bool Animal::hasEscaped() {
	return false;
}

bool Animal::isHuman() {
	return false;
}