#include"Plant.h"

// Konstruktor
Plant::Plant(int power, int initiative, int x,
	int y, int age, char symbol, World* world): 
	Organism(power, initiative, x, y, age, symbol, world){}

// Wykonanie akcji rozmnozenia
void Plant::action() {
	int randomNumber = world->randomNumber(1, 100);
	if (randomNumber <= 90) return;
	vector<vector<int>> possibleSpaces = world->possibleSpacesAround(x, y);
	if (possibleSpaces.size() <= 0) {
		return;
	}
	vector<int> chosenSpace = world->getRandomPossibleSpace(possibleSpaces);
	int destX = chosenSpace[0];
	int destY = chosenSpace[1];
	newPlant(destX, destY);
}

void Plant::collision(Organism* other_org) {
	return;
}

bool Plant::specialEffect(Organism* attacker) {
	return false;
}
