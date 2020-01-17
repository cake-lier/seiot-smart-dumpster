#include "EventHandlerManagerImpl.h"
#include "EventHandlerImpl.h"
#include "../physics/PhysicsConstants.h"
#include <Arduino.h>

EventHandlerManagerImpl::EventHandlerManagerImpl(PhysicalSystem &physics,
                                                 const Service &service,
                                                 bool &isAvailable,
                                                 int &currentWeight, 
                                                 bool &isWeightPolling)
    : handlers(new LinkedList<const EventHandler *>()),
      eventQueue(new LinkedList<const Event *>()),
      physics(physics),
      service(service),
      isAvailable(isAvailable),
      currentWeight(currentWeight),
      isWeightPolling(isWeightPolling) {
    auto getState = [&]() -> void {
        DynamicJsonDocument messageBody(50);
        messageBody["available"] = this->isAvailable;
        messageBody["weight"] = this->currentWeight;
        messageBody["success"] = true;
        this->service.sendMessage(MessageType::RESPONSE, "/state", messageBody);
    };
    this->addEventHandler(new EventHandlerImpl<decltype(getState)>(EventType::GET_STATE, getState));
    auto forceAvailable = [&]() -> void {
        this->physics.turnOffNotAvailableLed();
        this->isAvailable = true;
        this->currentWeight = 0;
        this->physics.turnOnAvailableLed();
        DynamicJsonDocument messageBody(24);
        messageBody["success"] = true;
        messageBody["available"] = this->isAvailable;
        this->service.sendMessage(MessageType::RESPONSE, "/state", messageBody);
    };
    this->addEventHandler(new EventHandlerImpl<decltype(forceAvailable)>(EventType::FORCE_STATE_AVAILABLE, forceAvailable));
    auto forceUnavailable = [&]() -> void {
        this->physics.turnOffAvailableLed();
        this->isAvailable = false;
        this->physics.turnOnNotAvailableLed();
        DynamicJsonDocument messageBody(24);
        messageBody["success"] = true;
        messageBody["available"] = this->isAvailable;
        this->service.sendMessage(MessageType::RESPONSE, "/state", messageBody);
    };
    this->addEventHandler(new EventHandlerImpl<decltype(forceUnavailable)>(EventType::FORCE_STATE_UNAVAILABLE, forceUnavailable));
    auto startDeposit = [&]() -> void {
        DynamicJsonDocument messageBody(24);
        if (this->isAvailable && !this->isWeightPolling) {
            this->isWeightPolling = true;
            messageBody["success"] = true;
        } else {
            messageBody["success"] = false;
        }
        this->service.sendMessage(MessageType::RESPONSE, "/deposit", messageBody);
    };
    this->addEventHandler(new EventHandlerImpl<decltype(startDeposit)>(EventType::BEGIN_DEPOSIT, startDeposit));
    auto endDeposit = [&]() -> void {
        DynamicJsonDocument messageBody(47);
        if (this->isWeightPolling) {
            this->isWeightPolling = false;
            int weightWaiting = this->physics.getWeight();
            if (weightWaiting + this->currentWeight >= MAX_WEIGHT) {
                this->isAvailable = false;
                this->physics.turnOffAvailableLed();
                this->physics.turnOnNotAvailableLed();
            }
            this->currentWeight += weightWaiting;
            messageBody["success"] = true;
            messageBody["weight"] = weightWaiting;
        } else {
            messageBody["success"] = false;
        }
        this->service.sendMessage(MessageType::RESPONSE, "/deposit", messageBody);
    };
    this->addEventHandler(new EventHandlerImpl<decltype(endDeposit)>(EventType::END_DEPOSIT, endDeposit));
}

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
