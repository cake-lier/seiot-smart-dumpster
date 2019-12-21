/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "EventSchedulerImpl.h"
#include "EventHandlerManagerImpl.h"
#include "../model/physics/PhysicalSystemImpl.h"
#include "handlers/ForceAvailableEventHandler.h"
#include "handlers/ForceUnavailableEventHandler.h"
#include "handlers/GetStateEventHandler.h"
#include "handlers/StartDepositEventHandler.h"
#include "handlers/EndDepositEventHandler.h"

EventSchedulerImpl::EventSchedulerImpl(void) 
    : manager(new EventHandlerManagerImpl()), physics(new PhysicalSystemImpl()), service(nullptr) {
    this->isAvailable = true;
    this->isWeightPolling = false;
    this->currentWeight = 0;
}

EventSchedulerImpl::~EventSchedulerImpl(void) {
    delete this->manager;
    delete this->physics;
    delete this->service;
}

void EventSchedulerImpl::init(void) {
    this->manager->addEventHandler(new ForceAvailableEventHandler(*this->physics, *this->service, this->isAvailable));
    this->manager->addEventHandler(new ForceUnavailableEventHandler(*this->physics, *this->service, this->isAvailable));
    this->manager->addEventHandler(new GetStateEventHandler(*this->service, this->isAvailable));
    this->manager->addEventHandler(new StartDepositEventHandler(*this->service, this->isAvailable, this->isWeightPolling));
    this->manager->addEventHandler(new EndDepositEventHandler(*this->service,
                                                              this->isAvailable,
                                                              this->isWeightPolling,
                                                              this->currentWeight));
}

void EventSchedulerImpl::step(void) {
    const Event * const nextEvent = this->manager->getNextEvent();
    switch (nextEvent->getType()) {
        default:
            break;
    }
    this->manager->triggerHandlers(nextEvent);
}
