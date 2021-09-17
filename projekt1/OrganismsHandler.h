#pragma once
#include"Antelope.h"
#include"Dandelion.h"
#include"Fox.h"
#include"Grass.h"
#include"Guarana.h"
#include"Human.h"
#include"PineBorscht.h"
#include"Sheep.h"
#include"Turtle.h"
#include"Wolf.h"
#include"WolfBerries.h"

class OrganismsHandler {
public:
	static Organism* newOrganism(int x, int y, char symbol, World* world);
};