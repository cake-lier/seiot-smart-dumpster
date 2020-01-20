/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __EVENT_HANDLER_MANAGER__
#define __EVENT_HANDLER_MANAGER__

#include "Event.h"
#include "EventHandler.h"

/*
 * Manager for the event handlers used in the system.
 */
class EventHandlerManager { 
    public:
        /*
         * Returns whether there is an event in the queue of events that needs to be handled.
         */
        virtual bool isNextEventAvailable(void) const = 0;
        /*
         * Returns the next event that needs to be handled.
         */
        virtual const Event *getNextEvent(void) = 0;
        /*
         * Adds an Event to the queue containing the events to be handled.
         */
        virtual void dispatchEvent(const Event * const event) = 0;
        /*
         * Adds an event handler to the list of handlers that can be used to manage events.
         */
        virtual void addEventHandler(const EventHandler * const handler) = 0;
        /*
         * Executes the right handlers for the given event, choosing from the ones present in the list of available handlers.
         */
        virtual void triggerHandlers(const Event * const event) const = 0;
        /*
         * Default destructor.
         */
        virtual ~EventHandlerManager(void) {}
};

#endif
