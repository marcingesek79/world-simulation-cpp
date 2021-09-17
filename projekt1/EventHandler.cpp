#include "EventHandler.h"

// Konstruktor
EventHandler::EventHandler(){}

// Dodaje event do wektora
void EventHandler::addEvent(string event) {
	events.push_back(event);
}

// Usuwa wszystkie eventy
void EventHandler::deleteEvents() {
	events.clear();
}

// Wypisuje wszystkie eventy
void EventHandler::printEvents() {
	for (int i = 0; i < events.size(); i++) {
		cout << events[i] << endl;
	}
	deleteEvents();
}

// Zwraca eventy
vector<string>* EventHandler::getEvents() {
	return &events;
}