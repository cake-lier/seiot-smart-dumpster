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
#define PERIOD 100 // milliseconds

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
    Message msg = this->commSystem->getMessage();
    const unsigned long int t0 = millis();
    this->openTime = this->openTime + (t0 - this->lastCheckedTime);
    this->lastCheckedTime = t0;
    std::vector<Event> queue = *(this->eventGenerator->generateEventFromMessage(msg));
    std::vector<Event> queue2 = *(this->eventGenerator->generatePeriodicEvent(this->openTime));
    queue.insert(queue.end(), queue2.begin(), queue2.end());
    for (int i = 0; i < queue.size(); i++) {
        // this->handlerManager->runEventHandler(queue[i]); // DEBUG:
    }
    // TODO: this lambda breaks everything
    /*for_each(queue.begin(), queue.end(), [=, *this](Event ev) -> void {
        this->handlerManager->runEventHandler(ev);
    });*/
    delay(PERIOD);
}