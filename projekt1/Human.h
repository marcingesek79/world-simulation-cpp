#pragma once
#include "Animal.h"


class Human : public Animal {
private:
	char dir;
	int powerCooldown;
	int powerDuration;
	bool isPowerActivated;
	bool isPowerOnCooldown;
public:
	Human(int x, int y, World* world);
	void newChild(int x, int y) override;
	void action();
	void escape();
	bool hasEscaped() override;
	vector<int> handleDir();
	void collision(Organism* other_org);
	bool isHuman() override;
	// Gettery & settery
	void setDir(char dir);
	char getDir();
	void setIsPowerActivated(bool value);
	bool getIsPowerActivated();
	void setIsPowerOnCooldown(bool value);
	bool getIsPowerOnCooldown();
	void setPowerCooldown(int cooldown);
	int getPowerCooldown();
	void setPowerDuration(int duration);
	int getPowerDuration();
	// Statusy
	string powerStatus();
	string cooldownStatus();
	string getName() override;
};