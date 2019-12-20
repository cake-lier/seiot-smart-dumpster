/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __EVENT_IMPL__
#define __EVENT_IMPL__

#include "Event.h"

/*
 * 
 */
class EventImpl: public Event { 
    public:
        /*
         * 
         */
        EventImpl(const EventType type);
        /*
         * Default destructor.
         */
        ~EventImpl(void);
        /*
         * 
         */
        EventType getType(void) const override;
    private:
        const EventType type;
};

#endif
