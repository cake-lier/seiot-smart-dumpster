/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __EVENT_HANDLER__
#define __EVENT_HANDLER__

#include "Event.h"

/*
 * 
 */
class EventHandler { 
    public:
        /*
         * 
         */
        virtual bool isForEvent(const Event &event) const = 0;
        /*
         * 
         */
        virtual void execute(void) const = 0;
        /*
         * Default destructor.
         */
        virtual ~EventHandler(void) {};
};

#endif
