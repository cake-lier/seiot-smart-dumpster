/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __HANDLER_MANAGER__
#define __HANDLER_MANAGER__

#include "Event.h"
#include "EventHandler.h"

/*
 * The class which has the responsibility of managing the handlers which have to be executed while this software is executing.
 * It can add a new event handler to the list of the already inserted ones or execute all the handlers that are bound to a
 * specified event that has happened.
 */
class HandlerManager {
    public:
        /*
         * It executes all the event handlers tied to the passed event.
         */
        virtual void runEventHandler(const Event event) const = 0;
        /*
         * It adds a new event handler to the list of the already inserted ones.
         */
        virtual void addEventHandler(const EventHandler * const handler) const = 0;
        /*
         * Default destructor.
         */
        virtual ~HandlerManager(void) {}
};

#endif