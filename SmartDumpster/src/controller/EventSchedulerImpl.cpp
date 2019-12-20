/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "EventSchedulerImpl.h"
#include "EventHandlerManagerImpl.h"
#include "../model/physics/PhysicalSystemImpl.h"
#include "handlers/ForceAvailableEventHandler.h"
#include "handlers/ForceUnavailableEventHandler.h"
#include "handlers/GetStateEventHandler.h"

EventSchedulerImpl::EventSchedulerImpl(void) 
    : manager(new EventHandlerManagerImpl()), physics(new PhysicalSystemImpl()), service(nullptr) {
    this->isAvailable = true;
    this->isWeightPolling = false;
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
}

void EventSchedulerImpl::step(void) {
    this->manager->triggerHandlers(this->manager->getNextEvent());
}
