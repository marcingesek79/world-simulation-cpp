#include<iostream>
#include"World.h"
#include"Human.h"
#include <conio.h>
#include<fstream>
#include"OrganismsHandler.h"
#define SLEEP_TIME 600
#define HUMAN_ALIVE false
#define ORGANISMS_COUNT 10
using namespace std;

// Konstruktor
World::World(int n, int m) {
	sizeX = n;
	sizeY = m;
	turn = 0;
	human = nullptr;
	isHumanAlive = HUMAN_ALIVE;
	matrix = new Organism**[n];
	for (int i = 0; i < n; i++)
	{
		matrix[i] = new Organism * [n];
	}
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			matrix[i][j] = nullptr;
		}
	}
	eventHandler = EventHandler();
}

// Rysowanie swiata gry
void World::drawWorld() {
	system("cls");
	cout << "Imie i nazwisko: Marcin Gesek, Nr Indeksu: 184580" << endl;
	cout << "Tura: " << turn << endl << endl;
	for (int i = 0; i < sizeX + 2; i++)
	{
		cout << "# ";
	}
	cout << endl;
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = -1; j < sizeX+1; j++)
		{
			if (j == -1) cout << "# ";
			else if (j == sizeX) cout << "#";
			else if (matrix[i][j] == nullptr) cout << ". ";
			else {
				matrix[i][j]->draw();
				cout << " ";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < sizeX + 2; i++)
	{
		cout << "# ";
	}
	cout << endl << endl;
}

// Wykonuje ture
void World::takeTurn() {
	drawWorld();
	if (turn == 0) {
		deleteFromOrganisms();
		sortOrganisms();
	}
	char dir, powerCmd;
	// Aktywacja umiejetnosci
	if (isHumanAlive) {
		dir = inputHandler();
		if (human->getIsPowerActivated() == false && !human->getIsPowerOnCooldown()) {
			powerCmd = specialPowerHandler();
			if (powerCmd == 't') human->setIsPowerActivated(true);
		}
	}
	int size = organisms.size();
	// Wykonywanie tur
	for (int i = 0; i < size; i++) {
		if (organisms[i] == nullptr) continue;
		if (dynamic_cast<Human*>(organisms[i]) && isHumanAlive) dynamic_cast<Human*>(organisms[i])->setDir(dir);
		organisms[i]->makeOlder();
		organisms[i]->action();
		drawWorld();
		Sleep(SLEEP_TIME);
	}
	// Status umiejetnosci
	if (isHumanAlive) {
		if (human->getIsPowerActivated()) {
			getEventHandler()->addEvent(human->powerStatus());
		}
		else if (human->getIsPowerOnCooldown()) {
			getEventHandler()->addEvent(human->cooldownStatus());
		}
	}
	turn++;
	drawWorld();
	eventHandler.printEvents();
	deleteFromOrganisms();
	sortOrganisms();
	fileHandler();
}

// Dodawanie organizmu
void World::addOrganism(Organism* organism) {
	int x = organism->getX();
	int y = organism->getY();
	if (matrix[y][x] == nullptr) {
		matrix[y][x] = organism;
	}
	organisms.push_back(organism);
}

// Dodawanie czlowieka
void World::addHuman(Human* human) {
	int x = human->getX();
	int y = human->getY();
	if (matrix[y][x] == nullptr) {
		matrix[y][x] = human;
	}
	organisms.push_back(human);
	this->human = human;
	isHumanAlive = true;
}

// Usuwa wszystkie umarle organizmy z organizmow
void World::deleteFromOrganisms() {
	if (organisms.empty() == false) {
		for (int i = organisms.size() - 1; i >= 0; i--) {
			if (organisms.at(i) == nullptr) {
				organisms.erase(organisms.begin() + i);
			}
		}
	}
}

// Nadaje organizmowi status nieaktywnego
void World::makeOrganismInactive(Organism* org) {
	for (int i = 0; i < organisms.size(); i++)
	{
		if (organisms[i] == nullptr) continue;
		if (organisms[i]->getX() == org->getX() &&
			organisms[i]->getY() == org->getY()) {
			organisms[i] = nullptr;
			return;
		}
	}
}

// Porownuje organizmy w kolejnosc inicjatywa->wiek
bool World::comparator(Organism* a, Organism* b) {
	if (a->getInitiative() > b->getInitiative()) return true;
	else if (a->getInitiative() == b->getInitiative()) {
		if (a->getAge() > b->getAge()) return true;
	}
	return false;
}

// Sortuje organizmy wedlug inicjatywy i wieku
void World::sortOrganisms() {
	sort(organisms.begin(), organisms.end(), comparator);
}

// Zwraca losowa liczbe z podanego przedzialiu
int World::randomNumber(int rangeStart, int rangeEnd) {
	int number = rand() % rangeEnd + rangeStart;
	return number;
}

// Zwraca pola, na ktore moze przejsc organizm
vector<vector<int>> World::possibleSpacesToWalk(int x, int y) {
	vector<vector<int>> possibleSpaces;
	int possibilites[3] = { -1, 0, 1 };
	for (int i = 0; i < 3; i++)
	{
		int toAddX = possibilites[i];
		for (int j = 0; j < 3; j++)
		{
			int toAddY = possibilites[j];
			if (toAddX == toAddY) continue;
			else if (toAddX == -toAddY) continue;
			else if (x + toAddX >= sizeX || x + toAddX < 0) continue;
			else if (y + toAddY >= sizeY || y + toAddY < 0) continue;
			else {
				vector<int> possibleSpace = { x + toAddX, y + toAddY };
				possibleSpaces.push_back(possibleSpace);
			}
		}
	}
	return possibleSpaces;
}

// Zwraca pola dookola jakiegos miejsca, ktore nie zawieraja organizmow
vector<vector<int>> World::possibleSpacesAround(int x, int y) {
	vector<vector<int>> possibleSpaces;
	int possibilites[3] = { -1, 0, 1 };
	for (int i = 0; i < 3; i++)
	{
		int toAddX = possibilites[i];
		for (int j = 0; j < 3; j++)
		{
			int toAddY = possibilites[j];
			if (x + toAddX >= sizeX || x + toAddX < 0) continue;
			else if (y + toAddY >= sizeY || y + toAddY < 0) continue;
			else if (toAddY == 0 && toAddX == 0) continue;
			else if (matrix[y + toAddY][x + toAddX] != nullptr) continue;
			else {
				vector<int> possibleSpace = { x + toAddX, y + toAddY };
				possibleSpaces.push_back(possibleSpace);
			}
		}
	}
	return possibleSpaces;
}

// Zwraca pola, na ktore moze przejsc organizm (bezpiecznie)
vector<vector<int>> World::possibleSpacesToWalkSafe(int x, int y, Organism* org) {
	vector<vector<int>> possibleSpaces;
	int possibilites[3] = { -1, 0, 1 };
	for (int i = 0; i < 3; i++)
	{
		int toAddX = possibilites[i];
		for (int j = 0; j < 3; j++)
		{
			int toAddY = possibilites[j];
			if (toAddX == toAddY) continue;
			else if (toAddX == -toAddY) continue;
			else if (x + toAddX >= sizeX || x + toAddX < 0) continue;
			else if (y + toAddY >= sizeY || y + toAddY < 0) continue;
			else {
				if (matrix[y + toAddY][x + toAddX] != nullptr) {
					if (matrix[y + toAddY][x + toAddX]->getPower() > org->getPower()) continue;
				}
				vector<int> possibleSpace = { x + toAddX, y + toAddY };
				possibleSpaces.push_back(possibleSpace);
			}
		}
	}
	return possibleSpaces;
}

// Zwraca pola, na ktore moga przejsc organizmy z zasiegiem ruchu 2
vector<vector<int>> World::possibleSpacesToJump(int x, int y) {
	vector<vector<int>> possibleSpaces;
	int possibilites[3] = { -2, 0, 2 };
	for (int i = 0; i < 3; i++)
	{
		int toAddX = possibilites[i];
		for (int j = 0; j < 3; j++)
		{
			int toAddY = possibilites[j];
			if (toAddX == toAddY) continue;
			else if (toAddX == -toAddY) continue;
			else if (x + toAddX >= sizeX || x + toAddX < 0) continue;
			else if (y + toAddY >= sizeY || y + toAddY < 0) continue;
			else {
				vector<int> possibleSpace = { x + toAddX, y + toAddY };
				possibleSpaces.push_back(possibleSpace);
			}
		}
	}
	return possibleSpaces;
}

// Zwraca pola, dookola jakiegos miejsca, ktore zawieraja organizmy
vector<vector<int>> World::spacesWithOrganismsAround(int x, int y) {
	vector<vector<int>> possibleSpaces;
	int possibilites[3] = { -1, 0, 1 };
	for (int i = 0; i < 3; i++)
	{
		int toAddX = possibilites[i];
		for (int j = 0; j < 3; j++)
		{
			int toAddY = possibilites[j];
			if (x + toAddX >= sizeX || x + toAddX < 0) continue;
			else if (y + toAddY >= sizeY || y + toAddY < 0) continue;
			else if (toAddY == 0 && toAddX == 0) continue;
			else if (matrix[y + toAddY][x + toAddX] != nullptr) {
				vector<int> possibleSpace = { x + toAddX, y + toAddY };
				possibleSpaces.push_back(possibleSpace);
			}
		}
	}
	return possibleSpaces;
}

// Zwraca wszystkie pola na swiecie
vector<vector<int>> World::allSpacesInMatrix() {
	vector<vector<int>> allSpaces;
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++) {
			vector<int> space;
			space.push_back(j);
			space.push_back(i);
			allSpaces.push_back(space);
		}
	}
	return allSpaces;
}

// Zwraca losowe jedno pole z podanych pol
vector<int> World::getRandomPossibleSpace(vector<vector<int>> vec) {
	int randomIndex = randomNumber(0, vec.size());
	vector<int> chosenSpace = vec[randomIndex];
	return chosenSpace;
}

// Zapisywanie swiata do pliku
void World::saveToFile() {
	string fileName;
	cout << "Podaj nazwe pliku: ";
	cin >> fileName;
	ofstream myFile(fileName + ".txt");
	myFile << sizeX << endl;
	myFile << sizeY << endl;
	myFile << turn << endl;
	myFile << (int)isHumanAlive << endl;
	myFile << organisms.size() << endl;
	for (int i = 0; i < organisms.size(); i++)
	{
		myFile << organisms[i]->getSymbol() << endl;
		myFile << organisms[i]->getPower() << endl;
		myFile << organisms[i]->getInitiative() << endl;
		myFile << organisms[i]->getAge() << endl;
		myFile << organisms[i]->getX() << endl;
		myFile << organisms[i]->getY() << endl;
		if (organisms[i]->getSymbol() == 'H') {
			myFile << human->getPowerCooldown() << endl;
			myFile << human->getPowerDuration() << endl;
			myFile << (int)human->getIsPowerActivated() << endl;
			myFile << (int)human->getIsPowerOnCooldown() << endl;
		}
	}
	cout << "Zapisano swiat" << endl;
	myFile.close();
}

// Wczytywanie swiata z pliku
World* World::loadFromFile() {
	string fileName, line;
	cout << "Podaj nazwe pliku: ";
	cin >> fileName;
	ifstream myFile(fileName + ".txt");
	int xSize, ySize, turn, n;
	bool iHA;
	myFile >> xSize;
	myFile >> ySize;
	World* newWorld = new World(xSize, ySize);
	myFile >> turn;
	newWorld->setTurns(turn);
	myFile >> iHA;
	newWorld->setIsHumanAlive(iHA);
	myFile >> n;
	for (int i = 0; i < n; i++)
	{
		int x, y, age, power, initiative;
		char symbol;
		myFile >> symbol;
		myFile >> power;
		myFile >> initiative;
		myFile >> age;
		myFile >> x;
		myFile >> y;
		Organism* newOrganism = OrganismsHandler::newOrganism(x, y, symbol, newWorld);
		newOrganism->setPower(power);
		newOrganism->setAge(age);
		newOrganism->setInitiative(initiative);
		if (symbol == 'H') {
			int powerCooldown, powerDuration;
			bool isPowerActivated, isPowerOnCooldown;
			myFile >> powerCooldown;
			myFile >> powerDuration;
			myFile >> isPowerActivated;
			myFile >> isPowerOnCooldown;
			newWorld->addHuman(dynamic_cast<Human*>(newOrganism));
			newWorld->human->setIsPowerActivated(isPowerActivated);
			newWorld->human->setIsPowerOnCooldown(isPowerOnCooldown);
			newWorld->human->setPowerCooldown(powerCooldown);
			newWorld->human->setPowerDuration(powerDuration);
			continue;
		}
		newWorld->addOrganism(newOrganism);
	}
	cout << "Wczytano swiat" << endl;
	_getch();
	myFile.close();
	return newWorld;
}

// Generowanie losowego swiata
void World::generateRandomWorld() {
	int count = ORGANISMS_COUNT;
	char symbols[] = { 'A', 'F', 'S', 'T', 'W', 'd', 't', 'g', 'b', 'x' };
	vector<vector<int>> spacesInMatrix = allSpacesInMatrix();
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			char symbol = symbols[i];
			vector<int> space = getRandomPossibleSpace(spacesInMatrix);
			while (matrix[space[1]][space[0]] != nullptr) {
				space = getRandomPossibleSpace(spacesInMatrix);
			}
			Organism* newOrganism = OrganismsHandler::newOrganism(space[0], space[1], symbol, this);
			addOrganism(newOrganism);
		}
	}
}

// Oblsuga plikow
void World::fileHandler() {
	string event = "Czy chcesz zapisac swiat? (t/n)";
	getEventHandler()->addEvent(event);
	getEventHandler()->printEvents();
	switch (_getch()) {
	case 't':
		saveToFile();
		break;
	case 'n':
		return;
		break;
	default:
		return;
		break;
	}
}

// Obsluga wejscia gracza
char World::inputHandler() {
	string event = "W ktora strone chcesz sie poruszyc?";
	getEventHandler()->addEvent(event);
	getEventHandler()->printEvents();
	unsigned char c, dir = '?';
	c = _getch();
	if ((int)c == 224) {
		unsigned char d = _getch();
		switch (d) {
		case 72:
			dir = 'w';
			break;
		case 75:
			dir = 'a';
			break;
		case 80:
			dir = 's';
			break;
		case 77:
			dir = 'd';
			break;
		default:
			dir = '?';
			break;
		}
	}
	return dir;
}

// Aktywacja umiejetnosci
char World::specialPowerHandler() {
	string event = "Czy chcesz aktywowac umiejetnosc? (t/n)";
	getEventHandler()->addEvent(event);
	getEventHandler()->printEvents();
	switch (_getch()) {
	case 't':
		return 't';
		break;
	case 'n':
		return 'n';
		break;
	default:
		return 'n';
		break;
	}
}

int World::getSizeX() {
	return sizeX;
}

int World::getSizeY() {
	return sizeY;
}

void World::setTurns(int turns) {
	turn = turns;
}

void World::setIsHumanAlive(bool value) {
	isHumanAlive = value;
}

bool World::getIsHumanAlive() {
	return isHumanAlive;
}

Organism* World::getHuman() {
	return human;
}

Organism*** World::getMatrix() {
	return matrix;
}

vector<Organism*>* World::getOrganisms() {
	return &organisms;
}

EventHandler* World::getEventHandler() {
	return &eventHandler;
}

int World::getOrganismsSize() {
	return organisms.size();
}

// Destruktor
World::~World() {
	for (int i = 0; i < sizeY; i++)
	{
		delete[] matrix[i];
	}
	delete matrix;
	delete human;
	organisms.clear();
}