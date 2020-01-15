/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __EVENT_HANDLER_IMPL__
#define __EVENT_HANDLER_IMPL__

#include "EventHandler.h"

/*
 * A handler, a callback function to execute when the event of associated type happens.
 */
template<class Function>
class EventHandlerImpl: public EventHandler { 
    public:
        /*
         * Constructor which creates a new EventHandler by passing the Event for which this handler should be triggered and the
         * callback to be executed when the handler has been triggered.
         */
        EventHandlerImpl(const Event type, Function handler);
        /*
         * Default destructor.
         */
        ~EventHandlerImpl(void);
        /*
         * It returns if this handler should be called for the given event.
         */
        bool isForEvent(const Event event) const override;
        /*
         * It executes this handler.
         */
        void execute(void) const override;
    private:
        const Event type;
        Function handler;
};

template<class Function>
EventHandlerImpl<Function>::EventHandlerImpl(const Event type, Function handler) : type(type), handler(handler) {}

template<class Function>
EventHandlerImpl<Function>::~EventHandlerImpl(void) {}

template<class Function>
bool EventHandlerImpl<Function>::isForEvent(const Event event) const {
    return this->type == event;
}

template<class Function>
void EventHandlerImpl<Function>::execute(void) const {
    this->handler();
}

#endif
