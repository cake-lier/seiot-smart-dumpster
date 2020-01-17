/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __EVENT__
#define __EVENT__

#include "EventType.h"

/*
 * 
 */
class Event { 
    public:
        /*
         * 
         */
        virtual EventType getType(void) const = 0;
        /*
         * Default destructor.
         */
        virtual ~Event(void) {}
};

#endif
