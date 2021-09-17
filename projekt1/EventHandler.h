#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class EventHandler {
private:
	vector<string> events;
public:
	EventHandler();
	void addEvent(string event);
	void printEvents();
	void deleteEvents();
	vector<string>* getEvents();
};