#include "EventGeneratorImpl.h"

#include <stdlib.h>

#define T_DELIVER 10000 // DEBUG: 60000 // milliseconds

using namespace std;

unsigned int EventGeneratorImpl::generateEventFromMessage(const Message message, Event **events) {
    unsigned int eventsNum;
    switch (message) {
        case Message::SET_TRASH_A:
            eventsNum = 2;
            *events = (Event *) malloc(eventsNum * sizeof(Event));
            (*events)[0] = Event::SET_TRASH_A;
            (*events)[1] = Event::START_DEPOSIT;
            break;
        case Message::SET_TRASH_B:        
            eventsNum = 2;
            *events = (Event *) malloc(eventsNum * sizeof(Event));
            (*events)[0] = (Event::SET_TRASH_B);
            (*events)[1] = (Event::START_DEPOSIT);
            break;
        case Message::SET_TRASH_C:         
            eventsNum = 2;
            *events = (Event *) malloc(eventsNum * sizeof(Event));
            (*events)[0] = (Event::SET_TRASH_C);
            (*events)[1] = (Event::START_DEPOSIT);
            break;
        case Message::START_DEPOSIT:         
            eventsNum = 1;
            *events = (Event *) malloc(eventsNum * sizeof(Event));
            (*events)[0] = (Event::START_DEPOSIT);
            break;
        case Message::END_DEPOSIT:        
            eventsNum = 1;
            *events = (Event *) malloc(eventsNum * sizeof(Event));
            (*events)[0] = (Event::END_DEPOSIT);
            break;
        case Message::KEEP_OPEN:         
            eventsNum = 1;
            *events = (Event *) malloc(eventsNum * sizeof(Event));
            (*events)[0] = (Event::KEEP_OPEN_REQUEST);
            break;
        default:        
            eventsNum = 1;
            *events = (Event *) malloc(eventsNum * sizeof(Event));
            (*events)[0] = (Event::EMPTY);
    }
    return eventsNum;
}

unsigned int EventGeneratorImpl::generatePeriodicEvent(const unsigned int timeSinceOpening, Event **events) {
    *events = (Event *) malloc(sizeof(Event));
    if (timeSinceOpening >= T_DELIVER) {
        (*events)[0] = (Event::END_DEPOSIT);
    } else {
        (*events)[0] = (Event::EMPTY);
    }
    return 1;
}