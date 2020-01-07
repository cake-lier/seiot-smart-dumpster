#ifndef __EVENT_GENERATOR_IMPL__
#define __EVENT_GENERATOR_IMPL__

#include "EventGenerator.h"

class EventGeneratorImpl : public EventGenerator {
    public:
        EventGeneratorImpl(void) {}
        ~EventGeneratorImpl(void) {}
        unsigned int generateEventFromMessage(const Message message, Event **events) override;
        unsigned int generatePeriodicEvent(const unsigned int timeSinceOpening, Event **events) override;
};

#endif