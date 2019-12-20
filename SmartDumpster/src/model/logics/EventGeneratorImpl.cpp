#include "EventGeneratorImpl.h"

#define T_DELIVER 60000 // milliseconds

using namespace std;

vector<Event> *EventGeneratorImpl::generateEventFromMessage(const Message message) {
    vector<Event> *ev = new vector<Event>();
    switch (message) {
        case Message::SET_TRASH_A: 
            ev->push_back(Event::SET_TRASH_A);
            ev->push_back(Event::START_DEPOSIT);
            break;
        case Message::SET_TRASH_B:
            ev->push_back(Event::SET_TRASH_B);
            ev->push_back(Event::START_DEPOSIT);
            break;
        case Message::SET_TRASH_C: 
            ev->push_back(Event::SET_TRASH_C);
            ev->push_back(Event::START_DEPOSIT);
            break;
        case Message::START_DEPOSIT: 
            ev->push_back(Event::START_DEPOSIT);
            break;
        case Message::END_DEPOSIT:
            ev->push_back(Event::END_DEPOSIT);
            break;
        case Message::KEEP_OPEN: 
            ev->push_back(Event::KEEP_OPEN_REQUEST);
            break;
        default:
            ev->push_back(Event::EMPTY);
    }
    return ev;
}

vector<Event> *EventGeneratorImpl::generatePeriodicEvent(const unsigned int timeSinceOpening) {
    vector<Event> *evs = new vector<Event>();
    if (timeSinceOpening >= T_DELIVER) {
        evs->push_back(Event::END_DEPOSIT);
    } else {
        evs->push_back(Event::EMPTY);
    }
    return evs;
}