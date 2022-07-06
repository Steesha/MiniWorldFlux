#include "pch.h"
#include "EventManager.h"

EventManager& EventManager::getInstance() {
	static EventManager instance_;
	return instance_;
}

void EventManager::reg(Event _Event, EventHandler _Handler) {
	_events.appendListener(_Event, _Handler);
}

void EventManager::call(Event _Event) {
	_events.dispatch(_Event);
}


