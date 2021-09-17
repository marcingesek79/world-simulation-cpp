#include "Turtle.h"

// Konstruktor
Turtle::Turtle(int x, int y, World* world):
	Animal(2, 1, x, y, 0, 'T', world){}

// Rozmnazanie sie
void Turtle::newChild(int x, int y) {
	Turtle* turtle = new Turtle (x, y, world);
	world->getMatrix()[y][x] = turtle;
	world->getOrganisms()->push_back(turtle);
	string event = "Narodzil sie zolw [" + to_string(x) +
		", " + to_string(y) + "]";
	world->getEventHandler()->addEvent(event);
}

// Wykonanie akcji
void Turtle::action() {
	int randomNumber = world->randomNumber(1, 100);
	if (randomNumber <= 75) return;
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

// Specjalna umiejetnosc
bool Turtle::hasDefended(int enemyPower) {
	if (enemyPower < 5) {
		string event = "Zolw obronil sie przed atakiem";
		world->getEventHandler()->addEvent(event);
		return true;
	}
	return false;
}

// Zwraca nazwe
string Turtle::getName() {
	return "'Zolw'";
}