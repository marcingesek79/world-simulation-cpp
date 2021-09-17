#pragma once
#include<iostream>
#include<Vector>
#include"Organism.h"
#include<Windows.h>
#include"EventHandler.h"
using namespace std;

class Organism;
class Animal;
class Human;

class World {
private:
	int sizeX;
	int sizeY;
	int turn;
	Human* human;
	bool isHumanAlive;
	Organism*** matrix;
	vector<Organism*> organisms;
	EventHandler eventHandler;
public:
	World(int n, int m);
	void drawWorld();
	void takeTurn();
	void addOrganism(Organism* organism);
	void addHuman(Human* human);
	void deleteFromOrganisms();
	void makeOrganismInactive(Organism* org);
	static bool comparator(Organism* a, Organism* b);
	void sortOrganisms();
	int randomNumber(int rangeStart, int rangeEnd);
	// Movement
	vector<vector<int>> possibleSpacesToWalk(int x, int y);
	vector<vector<int>> possibleSpacesAround(int x, int y);
	vector<vector<int>> possibleSpacesToWalkSafe(int x, int y, Organism* org);
	vector<vector<int>> possibleSpacesToJump(int x, int y);
	vector<vector<int>> spacesWithOrganismsAround(int x, int y);
	vector<vector<int>> allSpacesInMatrix();
	vector<int> getRandomPossibleSpace(vector<vector<int>> vec);
	// Zapisywanie/wczytywanie/handling
	void saveToFile();
	static World* loadFromFile();
	void generateRandomWorld();
	void fileHandler();
	char inputHandler();
	char specialPowerHandler();
	// Gettery&settery
	int getSizeX();
	int getSizeY();
	void setTurns(int turns);
	void setIsHumanAlive(bool value);
	bool getIsHumanAlive();
	Organism* getHuman();
	Organism*** getMatrix();
	vector<Organism*>* getOrganisms();
	EventHandler* getEventHandler();
	int getOrganismsSize();
	~World();
};