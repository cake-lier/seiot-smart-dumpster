#include "EventGeneratorImpl.h"

Event EventGeneratorImpl::generateEventFromMessage(const Message message) {
    Event ev;
    switch (message) {
        case Message::SET_TRASH_A: 
            ev = Event::SET_TRASH_A;
            break;
        case Message::SET_TRASH_B:
            ev = Event::SET_TRASH_B;
            break;
        case Message::SET_TRASH_C: 
            ev = Event::SET_TRASH_C;
            break;
        case Message::START_DEPOSIT: 
            ev = Event::START_DEPOSIT;
            break;
        case Message::END_DEPOSIT:
            ev = Event::END_DEPOSIT;
            break;
        case Message::KEEP_OPEN: 
            ev = Event::KEEP_OPEN_REQUEST;
            break;
        default:
            ev = Event::EMPTY;
    }
    return ev;
}