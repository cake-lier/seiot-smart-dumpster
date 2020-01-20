/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __EVENT_IMPL__
#define __EVENT_IMPL__

#include "Event.h"

/*
 * A class representing an event happened in the Edge.
 */
class EventImpl: public Event { 
    public:
        /*
         * Constructor, requires the type of the event being constructed.
         */
        EventImpl(const EventType type);
        /*
         * Default destructor.
         */
        ~EventImpl(void);
        /*
         * Returns the type of this event.
         */
        EventType getType(void) const override;
    private:
        const EventType type;
};

#endif
