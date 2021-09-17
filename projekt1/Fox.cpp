#include"Fox.h"

// Konstruktor
Fox::Fox(int x, int y, World* world):
	Animal(3, 7, x, y, 0, 'F', world){}

// Rozmnazanie sie
void Fox::newChild(int x, int y) {
	Fox* fox = new Fox(x, y, world);
	world->getMatrix()[y][x] = fox;
	world->getOrganisms()->push_back(fox);
	string event = "Narodzil sie lis [" + to_string(x) +
		", " + to_string(y) + "]";
	world->getEventHandler()->addEvent(event);
}

// Wykonanie akcji
void Fox::action() {
	vector<vector<int>> possibleSpaces = world->possibleSpacesToWalkSafe(x, y, this);
	if (possibleSpaces.size() <= 0) {
		return;
	}
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

// Zwraca nazwe
string Fox::getName() {
	return "'Lis'";
}