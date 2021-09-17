#include<iostream>
#include"World.h"
#include"Animal.h"
#include"Wolf.h"
#include"Sheep.h"
#include"Fox.h"
#include"Turtle.h"
#include"Antelope.h"
#include"Grass.h"
#include"Dandelion.h"
#include"Guarana.h"
#include"WolfBerries.h"
#include"PineBorscht.h"
#include"Human.h"

int main() {
	srand(time(NULL));
	// Zmienne pomocnicze
	string n = "";
	char ans = NULL;
	char ans2 = NULL;
	World* world;

	// Tworzenie swiata
	cout << "Czy chcesz wgrac zapis? (t/n)";
	cin >> ans;
	switch (ans) {
		case 't':
			world = World::loadFromFile();
			break;
		case 'n': default:
			int x, y;
			cout << "Podaj x: ";
			cin >> x;
			cout << "Podaj y: ";
			cin >> y;
			world = new World(x, y);
			Human* human = new Human(x - 1, y - 1, world);
			world->addHuman(human);
			world->generateRandomWorld();
			break;
	}

	// Glowna petla
	while (n != "end") {
		world->takeTurn();
		cout << "Nowa tura..." << endl;
		cin >> n;
	}

	delete world;
	return 0;
}