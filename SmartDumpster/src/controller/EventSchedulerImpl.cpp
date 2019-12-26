/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "EventSchedulerImpl.h"
#include "EventHandlerManagerImpl.h"
#include "../model/physics/PhysicalSystemImpl.h"
#include "../model/service/ServiceImpl.h"
#include "../model/logics/ForceAvailableEventHandler.h"
#include "../model/logics/ForceUnavailableEventHandler.h"
#include "../model/logics/GetStateEventHandler.h"
#include "../model/logics/StartDepositEventHandler.h"
#include "../model/logics/EndDepositEventHandler.h"
#include "EventImpl.h"
#include "EventType.h"
#include "../model/physics/PhysicsConstants.h"

EventSchedulerImpl::EventSchedulerImpl(void) 
    : manager(new EventHandlerManagerImpl()), physics(new PhysicalSystemImpl()), service(new ServiceImpl()) {
    this->isAvailable = true;
    this->isWeightPolling = false;
    this->currentWeight = 0;
    this->physics->turnOnAvailableLed();
    this->manager->addEventHandler(new ForceAvailableEventHandler(*this->physics,
                                                                  *this->service,
                                                                  this->isAvailable,
                                                                  this->currentWeight));
    this->manager->addEventHandler(new ForceUnavailableEventHandler(*this->physics, *this->service, this->isAvailable));
    this->manager->addEventHandler(new GetStateEventHandler(*this->service, this->isAvailable, this->currentWeight));
    this->manager->addEventHandler(new StartDepositEventHandler(*this->service, this->isAvailable, this->isWeightPolling));
    this->manager->addEventHandler(new EndDepositEventHandler(*this->physics,
                                                              *this->service,
                                                              this->isAvailable,
                                                              this->isWeightPolling,
                                                              this->currentWeight));
}

EventSchedulerImpl::~EventSchedulerImpl(void) {
    delete this->manager;
    delete this->physics;
    delete this->service;
}

void EventSchedulerImpl::step(void) {
    // Message transformation into events
    if (this->service->isMessageAvailable()) {
        const Message * const msg = this->service->receiveMessage();
        if (msg->getResource() == "/state") {
            if (msg->getType() == MessageType::READ) {
                this->manager->dispatchEvent(new EventImpl(EventType::GET_STATE));
            } else if (msg->getType() == MessageType::MODIFY) {
                this->manager->dispatchEvent(new EventImpl(msg->getPayload()["available"].as<bool>()
                                                           ? EventType::FORCE_STATE_AVAILABLE
                                                           : EventType::FORCE_STATE_UNAVAILABLE));
            }
        } else if (msg->getResource() == "/deposit") {
            const JsonDocument payload = msg->getPayload();
            if (payload["deposit"].as<String>() == "begin") {
                this->manager->dispatchEvent(new EventImpl(EventType::BEGIN_DEPOSIT));
            } else if (payload["deposit"].as<String>() == "end") {
                this->manager->dispatchEvent(new EventImpl(EventType::END_DEPOSIT));
            }
        }
        delete msg;
    }
    // If waiting for user to end deposit keep watching what happens with weight, so as to not exceed with weight
    if (this->isWeightPolling) {
        int weightWaiting = this->physics->getWeight();
        if (weightWaiting + this->currentWeight >= MAX_WEIGHT) {
            DynamicJsonDocument messageBody(47);
            messageBody["success"] = true;
            messageBody["weight"] = weightWaiting;
            this->service->sendMessage(MessageType::MODIFY, "/deposit/early_end", messageBody);
            this->isWeightPolling = false;
            this->isAvailable = false;
            this->physics->turnOffAvailableLed();
            this->physics->turnOnNotAvailableLed();
            this->currentWeight += weightWaiting;
        }
    }
    // Handling of next event
    if (this->manager->isNextEventAvailable()) {
        this->manager->triggerHandlers(this->manager->getNextEvent());
    }
}
