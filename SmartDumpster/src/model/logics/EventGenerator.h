#ifndef __EVENT_GENERATOR__
#define __EVENT_GENERATOR__

#include "../communication/Message.h"
#include "Event.h"

class EventGenerator {
    public:
        virtual Event generateEventFromMessage(Message) = 0;
};

#endif