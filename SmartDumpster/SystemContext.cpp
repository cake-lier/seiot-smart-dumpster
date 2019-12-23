/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "SystemContext.h"
#include "src/controller/EventSchedulerImpl.h"
#include <Arduino.h>

#define PERIOD 20UL          // milliseconds

SystemContext *SystemContext::SINGLETON = nullptr;

SystemContext *SystemContext::getInstance(void) {
    return SINGLETON;
}

void SystemContext::init(void) {
    if (SINGLETON == nullptr) {
        SINGLETON = new SystemContext();
    }
}

SystemContext::SystemContext(void): scheduler(new EventSchedulerImpl()) {}

SystemContext::~SystemContext(void) {
    delete this->scheduler;
}

void SystemContext::run(void) {
    const unsigned long int t0 = millis();
    this->scheduler->step();
    delay(PERIOD - (millis() - t0));
}
