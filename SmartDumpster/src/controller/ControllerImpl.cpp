#include "ControllerImpl.h"
#include "../model/communication/CommunicationSystemImpl.h"
#include "../model/communication/MessageParserImpl.h"
#include "../model/physics/PhysicalSystemImpl.h"
#include "../model/logics/HandlerManagerImpl.h"
#include "../model/logics/EventGeneratorImpl.h"
#include <Arduino.h>
#include <algorithm>
#include <vector>

#define BT_RX 3
#define BT_TX 2
#define PERIOD 250 // milliseconds

ControllerImpl::ControllerImpl(SoftwareSerial *btc) {
    this->physicalSystem = new PhysicalSystemImpl();
    MessageParser *parser = new MessageParserImpl();
    this->commSystem = new CommunicationSystemImpl(btc, parser);
    this->handlerManager = new HandlerManagerImpl(this->physicalSystem, this->commSystem, &(this->openTime));
    this->eventGenerator = new EventGeneratorImpl();
    this->openTime = 0;
    this->lastCheckedTime = millis();
}

ControllerImpl::~ControllerImpl(void) {
    delete this->physicalSystem;
    delete this->commSystem;
    delete this->handlerManager;
    delete this->eventGenerator;
}

void ControllerImpl::run(void) {
    Event *events;
    unsigned int numEvents;
    Message msg = this->commSystem->getMessage();
    if (this->physicalSystem->isServoOpen()) {
        const unsigned long int t0 = millis();
        this->openTime = this->openTime + (t0 - this->lastCheckedTime);
        this->lastCheckedTime = t0;
    }
    numEvents = this->eventGenerator->generateEventFromMessage(msg, &events);
    for (int i = 0; i < numEvents; i++) {
        if (events[i] == Event::START_DEPOSIT) {
            this->lastCheckedTime = millis();
        }
        this->handlerManager->runEventHandler(events[i]);
    }
    free((void *) events);
    numEvents = this->eventGenerator->generatePeriodicEvent(this->openTime, &events);
    for (int i = 0; i < numEvents; i++) {
        this->handlerManager->runEventHandler(events[i]);
    }
    free((void *) events);
    delay(PERIOD);
}