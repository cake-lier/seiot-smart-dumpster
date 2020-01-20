/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __EVENT_HANDLER_MANAGER_IMPL__
#define __EVENT_HANDLER_MANAGER_IMPL__

#include "EventHandlerManager.h"
#include "../physics/PhysicalSystem.h"
#include "../service/Service.h"
#include <LinkedList.h>

/*
 * Manager for the event handlers used in the system.
 */
class EventHandlerManagerImpl: public EventHandlerManager { 
    public:
        /*
         * Default constructor. Requires a PhysicalSystem, on which changes, depending on the events handled, will be shown,
         * a Service to manage communication with the external Service system and some variables that represent the 
         * current state of the system (availability, weight currently held, whether weight is being periodically checked or not).
         */
        EventHandlerManagerImpl(PhysicalSystem &physics,
                                const Service &service,
                                bool &isAvailable,
                                int &currentWeight, 
                                bool &isWeightPolling);
        /*
         * Default destructor.
         */
        ~EventHandlerManagerImpl(void);
        /*
         * Returns whether there is an event in the queue of events that needs to be handled.
         */
        bool isNextEventAvailable(void) const override;
        /*
         * Returns the next event that needs to be handled.
         */
        const Event *getNextEvent(void) override;
        /*
         * Adds an Event to the queue containing the events to be handled.
         */
        void dispatchEvent(const Event * const event) override;
        /*
         * Adds an event handler to the list of handlers that can be used to manage events.
         */
        void addEventHandler(const EventHandler * const handler) override;
        /*
         * Executes the right handlers for the given event, choosing from the ones present in the list of available handlers.
         */
        void triggerHandlers(const Event * const event) const override;
    private:
        LinkedList<const EventHandler *> * const handlers;
        LinkedList<const Event *> * const eventQueue;
        PhysicalSystem &physics;
        const Service &service;
        bool &isAvailable;
        int &currentWeight;
        bool &isWeightPolling;
};

#endif
