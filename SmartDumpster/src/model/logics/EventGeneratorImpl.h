#ifndef __EVENT_GENERATOR_IMPL__
#define __EVENT_GENERATOR_IMPL__

#include "EventGenerator.h"

class EventGeneratorImpl : public EventGenerator {
    public:
        EventGeneratorImpl(void) {}
        ~EventGeneratorImpl(void) {}
        std::vector<Event> *generateEventFromMessage(const Message message) override;
        std::vector<Event> *generatePeriodicEvent(const unsigned int timeSinceOpening) override;
};

#endif