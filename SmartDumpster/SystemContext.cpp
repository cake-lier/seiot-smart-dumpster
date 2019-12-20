/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "SystemContext.h"
#include "src/model/communication/MessageParserImpl.h"
#include "src/model/communication/CommunicationSystemImpl.h"
#include "src/model/physics/PhysicalSystemImpl.h"
#include "src/model/logics/HandlerManagerImpl.h"
#include "src/model/logics/EventGeneratorImpl.h"
#include <Arduino.h>

#define BT_RX 3
#define BT_TX 2
#define OPEN_TIME 60000 // milliseconds
#define PERIOD 125 // milliseconds

SystemContext *SystemContext::SINGLETON = nullptr;

SystemContext *SystemContext::getInstance(void) {
    return SINGLETON;
}

SystemContext::SystemContext(void) {
    this->physicalSystem = new PhysicalSystemImpl();
    this->commSystem = new CommunicationSystemImpl(BT_TX, BT_RX, new MessageParserImpl());
    this->handlerManager = new HandlerManagerImpl(this->physicalSystem, &(this->openTime));
    this->eventGenerator = new EventGeneratorImpl();
    this->openTime = 0;
    this->lastCheckedTime = millis();
}

SystemContext::~SystemContext(void) {
    delete this->physicalSystem;
    delete this->commSystem;
}

void SystemContext::run(void) {
    // TODO:
    Message msg = this->commSystem->getMessage();
    this->handlerManager->runEventHandler(this->eventGenerator->generateEventFromMessage(msg));
    const unsigned long int t0 = millis();
    this->openTime = this->openTime + (t0 - this->lastCheckedTime);
    this->lastCheckedTime = t0;
    delay(PERIOD);
}

void SystemContext::init(void) {
}
