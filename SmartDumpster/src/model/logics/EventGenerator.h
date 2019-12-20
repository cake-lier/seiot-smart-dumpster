#ifndef __EVENT_GENERATOR__
#define __EVENT_GENERATOR__

#include "../communication/Message.h"
#include "Event.h"
#include <vector>

class EventGenerator {
    public:
        virtual std::vector<Event> *generateEventFromMessage(Message) = 0;
        virtual std::vector<Event> *generatePeriodicEvent(unsigned int) = 0; // TODO: change name
};

#endif