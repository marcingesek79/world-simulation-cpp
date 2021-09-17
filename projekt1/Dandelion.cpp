#include "Dandelion.h"

// Konstruktor
Dandelion::Dandelion(int x, int y, World* world) :
	Plant(0, 0, x, y, 0, 'd', world){}

// Zasianie nowej rosliny
void Dandelion::newPlant(int x, int y) {
	Dandelion* dandelion = new Dandelion(x, y, world);
	world->getMatrix()[y][x] = dandelion;
	world->getOrganisms()->push_back(dandelion);
	string event = "Zasiano mlecz [" + to_string(x) +
		", " + to_string(y) + "]";
	world->getEventHandler()->addEvent(event);
}

// Wykonanie akcji
void Dandelion::action() {
	for (int i = 0; i < 3; i++)
	{
		int randomNumber = world->randomNumber(1, 100);
		if (randomNumber <= 90) continue;
		vector<vector<int>> possibleSpaces = world->possibleSpacesAround(x, y);
		if (possibleSpaces.size() <= 0) {
			return;
		}
		vector<int> chosenSpace = world->getRandomPossibleSpace(possibleSpaces);
		int destX = chosenSpace[0];
		int destY = chosenSpace[1];
		newPlant(destX, destY);
	}
}

// Zwraca nazwe
string Dandelion::getName() {
	return "'Mlecz'";
}