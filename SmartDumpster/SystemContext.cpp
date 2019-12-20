/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "SystemContext.h"
#include "src/model/communication/MessageParserImpl.h"
#include "src/model/communication/CommunicationSystemImpl.h"
#include "src/model/physics/PhysicalSystemImpl.h"
#include "src/model/logics/HandlerManagerImpl.h"
#include "src/model/logics/EventGeneratorImpl.h"
#include <Arduino.h>
#include <algorithm>
#include <vector>

#define BT_RX 3
#define BT_TX 2
#define PERIOD 100 // milliseconds

SystemContext *SystemContext::SINGLETON = nullptr;

SystemContext *SystemContext::getInstance(void) {
    return SINGLETON;
}

SystemContext::SystemContext(void) {
    this->physicalSystem = new PhysicalSystemImpl();
    this->commSystem = new CommunicationSystemImpl(BT_TX, BT_RX, new MessageParserImpl());
    if (this->commSystem) { // DEBUG:
        Serial.println("Comm system not null"); // DEBUG:
    } // DEBUG:
    this->handlerManager = new HandlerManagerImpl(this->physicalSystem, this->commSystem, &(this->openTime));
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
    Serial.println("getting msg"); // DEBUG:
    delay(2000); // DEBUG:
    // Message msg = 
    this->commSystem->sendMessage(Message::EMPTY);
    Serial.println("got msg"); // DEBUG:
    /*const unsigned long int t0 = millis();
    this->openTime = this->openTime + (t0 - this->lastCheckedTime);
    this->lastCheckedTime = t0;
    std::vector<Event> queue = *(this->eventGenerator->generateEventFromMessage(msg));
    std::vector<Event> queue2 = *(this->eventGenerator->generatePeriodicEvent(this->openTime));
    queue.insert(queue.end(), queue2.begin(), queue2.end());
    Serial.println("got events"); // DEBUG:
    for_each(queue.begin(), queue.end(), [=, *this](Event ev) -> void {
        this->handlerManager->runEventHandler(ev);
    });
    delay(PERIOD);
    */
}

void SystemContext::init(void) {
}
