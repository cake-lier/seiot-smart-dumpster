#ifndef __EVENT_GENERATOR_IMPL__
#define __EVENT_GENERATOR_IMPL__

#include "EventGenerator.h"

class EventGeneratorImpl : public EventGenerator {
    public:
        EventGeneratorImpl();
        ~EventGeneratorImpl() {}
        Event generateEventFromMessage(const Message message) override;
};

#endif