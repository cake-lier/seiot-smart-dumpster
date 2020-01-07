#ifndef __EVENT_GENERATOR__
#define __EVENT_GENERATOR__

#include "../communication/Message.h"
#include "Event.h"
#include <vector>

class EventGenerator {
    public:
        virtual unsigned int generateEventFromMessage(Message, Event **) = 0;
        virtual unsigned int generatePeriodicEvent(unsigned int, Event **) = 0; // TODO: change name
};

#endif