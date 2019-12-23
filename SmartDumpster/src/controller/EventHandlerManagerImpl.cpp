#include "EventHandlerManagerImpl.h"
#include <Arduino.h>

EventHandlerManagerImpl::EventHandlerManagerImpl(void)
    : handlers(new LinkedList<const EventHandler *>()), eventQueue(new LinkedList<const Event *>()) {}

EventHandlerManagerImpl::~EventHandlerManagerImpl(void) {
    for (int i = 0; i < this->handlers->size(); i++) {
        delete this->handlers->get(i);
    }
    delete this->handlers;
    for (int i = 0; i < this->eventQueue->size(); i++) {
        delete this->eventQueue->get(i);
    }
    delete this->eventQueue;
}

bool EventHandlerManagerImpl::isNextEventAvailable(void) const {
    noInterrupts();
    bool available = this->eventQueue->size() != 0;
    interrupts();
    return available;
}

const Event *EventHandlerManagerImpl::getNextEvent(void) {
    noInterrupts();
    const Event * nextEvent = this->eventQueue->shift();
    interrupts();
    return nextEvent;
}

void EventHandlerManagerImpl::dispatchEvent(const Event * const event) {
    noInterrupts();
    this->eventQueue->add(event);
    interrupts();
}

void EventHandlerManagerImpl::addEventHandler(const EventHandler * const handler) {
    this->handlers->add(handler);
}

void EventHandlerManagerImpl::triggerHandlers(const Event * const event) const {
    for (int i = 0; i < this->handlers->size(); i++) {
        if (this->handlers->get(i)->isForEvent(*event)) {
            this->handlers->get(i)->execute();
        }
    }
    delete event;
}
