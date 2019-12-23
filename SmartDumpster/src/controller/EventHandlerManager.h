/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __EVENT_HANDLER_MANAGER__
#define __EVENT_HANDLER_MANAGER__

#include "Event.h"
#include "handlers/EventHandler.h"

/*
 * 
 */
class EventHandlerManager { 
    public:
        /*
         * 
         */
        virtual bool isNextEventAvailable(void) const = 0;
        /*
         * 
         */
        virtual const Event *getNextEvent(void) = 0;
        /*
         * 
         */
        virtual void dispatchEvent(const Event * const event) = 0;
        /*
         * 
         */
        virtual void addEventHandler(const EventHandler * const handler) = 0;
        /*
         * 
         */
        virtual void triggerHandlers(const Event * const event) const = 0;
        /*
         * Default destructor.
         */
        virtual ~EventHandlerManager(void) {}
};

#endif
