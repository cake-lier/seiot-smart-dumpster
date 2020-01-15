/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __EVENT_HANDLER__
#define __EVENT_HANDLER__

#include "Event.h"

/*
 * A handler, a callback function to execute when the event of associated type happens. 
 */
class EventHandler { 
    public:
        /*
         * It returns if this handler should be called for the given event.
         */
        virtual bool isForEvent(const Event event) const = 0;
        /*
         * It executes this handler.
         */
        virtual void execute(void) const = 0;
        /*
         * Default destructor.
         */
        virtual ~EventHandler(void) {};
};

#endif
