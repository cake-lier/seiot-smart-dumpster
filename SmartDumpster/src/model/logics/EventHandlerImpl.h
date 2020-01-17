/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __ABSTRACT_EVENT_HANDLER__
#define __ABSTRACT_EVENT_HANDLER__

#include "EventHandler.h"
#include "EventType.h"

/*
 * 
 */
template<class Function>
class EventHandlerImpl: public EventHandler { 
    public:
        /*
         *
         */
        EventHandlerImpl(const EventType type, Function handler);
        /*
         * Default destructor.
         */
        ~EventHandlerImpl(void);
        /*
         * 
         */
        bool isForEvent(const Event &event) const override;
        /*
         * 
         */
        void execute(void) const override;
    private:
        EventType type;
        Function handler;
};

template<class Function>
EventHandlerImpl<Function>::EventHandlerImpl(const EventType type, Function handler) : handler(handler) {
    this->type = type;
}

template<class Function>
EventHandlerImpl<Function>::~EventHandlerImpl(void) {}

template<class Function>
bool EventHandlerImpl<Function>::isForEvent(const Event &event) const {
    return event.getType() == this->type;
}

template<class Function>
void EventHandlerImpl<Function>::execute(void) const {
    this->handler();
}

#endif
