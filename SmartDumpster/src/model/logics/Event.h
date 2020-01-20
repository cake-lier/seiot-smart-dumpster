/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __EVENT__
#define __EVENT__

#include "EventType.h"

/*
 * A class representing an event happened in the Edge.
 */
class Event { 
    public:
        /*
         * Returns the type of this event. 
         */
        virtual EventType getType(void) const = 0;
        /*
         * Default destructor.
         */
        virtual ~Event(void) {}
};

#endif
