#include "Antelope.h"

// Konstruktor
Antelope::Antelope(int x, int y, World* world):
	Animal(4, 4, x, y, 0, 'A', world){}

// Rozmnazanie sie
void Antelope::newChild(int x, int y) {
	Antelope* antelope = new Antelope(x, y, world);
	world->getMatrix()[y][x] = antelope;
	world->getOrganisms()->push_back(antelope);
	string event = "Narodzila sie antylopa [" + to_string(x) +
		", " + to_string(y) + "]";
	world->getEventHandler()->addEvent(event);
}

// Wykonanie akcji
void Antelope::action() {
	vector<vector<int>> possibleSpaces = world->possibleSpacesToJump(x, y);
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

// Ucieczka
bool Antelope::hasEscaped() {
	int randomNumber = world->randomNumber(1, 100);
	if (randomNumber <= 50) {
		vector<vector<int>> possibleSpaces = world->possibleSpacesAround(x, y);
		vector<int> cell = world->getRandomPossibleSpace(possibleSpaces);
		string event = "Antylopa uciekla przed walka ";
		event += "z pola [" + to_string(x) + ", " + to_string(y) + "] ";
		move(cell[0], cell[1]);
		
		event += "na pole [" + to_string(cell[0]) + ", " + to_string(cell[1]) + "]";
		world->getEventHandler()->addEvent(event);
		return true;
	}
	return false;
}

// Zwraca nazwe
string Antelope::getName() {
	return "'Antylopa'";
}