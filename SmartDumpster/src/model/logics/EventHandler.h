/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __EVENT_HANDLER__
#define __EVENT_HANDLER__

#include "Event.h"

/*
 * An handler for the events happening in the system.
 */
class EventHandler { 
    public:
        /*
         * Returns whether this EventHandler is for the given Event or not.
         */
        virtual bool isForEvent(const Event &event) const = 0;
        /*
         * Executes the event handler. 
         */
        virtual void execute(void) const = 0;
        /*
         * Default destructor.
         */
        virtual ~EventHandler(void) {};
};

#endif
