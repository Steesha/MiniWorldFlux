#pragma once
#include <eventpp/eventdispatcher.h>
#include "Events.h"

#define MakeHandler(_This, _Handler) std::bind(_Handler, _This)

typedef Events Event;
typedef void* EventParam;
typedef std::function<void()> EventHandler;

class EventManager {

public:

    static EventManager& getInstance();

    void reg(Event _Name, EventHandler _Handler);
    void call(Event _Name);
	
    EventManager(EventManager&&) = delete;
    EventManager(const EventManager&) = delete;
    void operator= (const EventManager&) = delete;

private:
    EventManager() = default;
    ~EventManager() = default;

    eventpp::EventDispatcher<Event, void()> _events;

};


