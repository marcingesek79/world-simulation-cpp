#include "Human.h"

// Konstruktor
Human::Human(int x, int y, World* world) :
	Animal(5, 4, x, y, 0, 'H', world) {
	dir = NULL;
	powerCooldown = 5;
	powerDuration = 5;
	isPowerActivated = false;
	isPowerOnCooldown = false;
}

// Rozmnazanie sie
void Human::newChild(int x, int y) {
	return;
}

// Wykonanie akcji
void Human::action() {
	if (isPowerActivated) {
		powerDuration--;
	}
	else if (isPowerOnCooldown) {
		powerCooldown--;
	}
	if (powerDuration <= 0) {
		powerCooldown = 5;
		powerDuration = 5;
		isPowerActivated = false;
		isPowerOnCooldown = true;
	}
	if (powerCooldown <= 0 && isPowerOnCooldown) {
		isPowerOnCooldown = false;
		powerCooldown = 5;
	}
	vector<int> chosenSpace = handleDir();
	if (chosenSpace.size() <= 0) return;
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

// Specjalna zdolnosc
void Human::escape() {
	vector<vector<int>> possibleSpaces = world->possibleSpacesAround(x, y);
	vector<int> cell = world->getRandomPossibleSpace(possibleSpaces);
	string event = "Czlowiek jest niesmiertelny i ucieka ";
	move(cell[0], cell[1]);
	event += "na pole [" + to_string(cell[0]) + ", " + to_string(cell[1]) + "]";
	world->getEventHandler()->addEvent(event);
}

// Specjalna zdolnosc
bool Human::hasEscaped() {
	if (isPowerActivated) {
		escape();
		return true;
	}
	return false;
}

// Nastepne pole do przejscia
vector<int> Human::handleDir() {
	vector<int> nextSpace;
	switch (dir) {
	case 'w':
		if (y > 0) {
			nextSpace.push_back(x);
			nextSpace.push_back(y - 1);
		}
		break;
	case 'a':
		if (x > 0) {
			nextSpace.push_back(x - 1);
			nextSpace.push_back(y);
		}
		break;
	case 's':
		if (y < world->getSizeY() - 1) {
			nextSpace.push_back(x);
			nextSpace.push_back(y + 1);
		}
		break;
	case 'd':
		if (x < world->getSizeX() - 1) {
			nextSpace.push_back(x + 1);
			nextSpace.push_back(y);
		}
		break;
	case '?':
		return nextSpace;
		break;
	}
	return nextSpace;
}

// Obsluga kolizji - specjalna zdolnosc
void Human::collision(Organism* other_org) {
	if (dynamic_cast<Animal*>(other_org)) {
		if (other_org->getPower() > power && isPowerActivated) {
			escape();
			return;
		}
		battle(other_org);
	}
	else if (dynamic_cast<Plant*>(other_org)) {
		if (other_org->getPower() > power && isPowerActivated) {
			escape();
			return;
		}
		eatPlant(other_org);
	}
}

bool Human::isHuman() {
	return true;
}

void Human::setDir(char dir) {
	this->dir = dir;
}

char Human::getDir() {
	return dir;
}

void Human::setIsPowerActivated(bool value) {
	isPowerActivated = value;
}

bool Human::getIsPowerActivated() {
	return isPowerActivated;
}

void Human::setIsPowerOnCooldown(bool value) {
	isPowerOnCooldown = value;
}

bool Human::getIsPowerOnCooldown() {
	return isPowerOnCooldown;
}

void Human::setPowerCooldown(int cooldown) {
	powerCooldown = cooldown;
}

int Human::getPowerCooldown() {
	return powerCooldown;
}

void Human::setPowerDuration(int duration) {
	powerDuration = duration;
}

int Human::getPowerDuration() {
	return powerDuration;
}

string Human::powerStatus() {
	string event = "Umiejetnosc jest aktywowana, pozostale tury: " + to_string(powerDuration);
	return event;
}

string Human::cooldownStatus() {
	string event = "Umiejetnosc bedzie gotowa za: " + to_string(powerCooldown);
	return event;
}

string Human::getName() {
	return "'Czlowiek'";
}