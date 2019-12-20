/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __EVENT_HANDLER_MANAGER_IMPL__
#define __EVENT_HANDLER_MANAGER_IMPL__

#include "EventHandlerManager.h"
#include <LinkedList.h>

/*
 * 
 */
class EventHandlerManagerImpl: public EventHandlerManager { 
    public:
        /*
         * Default constructor.
         */
        EventHandlerManagerImpl(void);
        /*
         * Default destructor.
         */
        ~EventHandlerManagerImpl(void);
        /*
         * 
         */
        const Event *getNextEvent(void) override;
        /*
         * 
         */
        void dispatchEvent(const Event * const event) override;
        /*
         * 
         */
        void addEventHandler(const EventHandler * const handler) override;
        /*
         * 
         */
        void triggerHandlers(const Event * const event) const override;
    private:
        LinkedList<const EventHandler *> * const handlers;
        LinkedList<const Event *> * const eventQueue;
};

#endif
