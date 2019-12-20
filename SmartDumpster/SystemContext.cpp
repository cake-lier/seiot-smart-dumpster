/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "SystemContext.h"
#include "src/controller/EventSchedulerImpl.h"
#include <Arduino.h>

#define PERIOD 125UL          // milliseconds

SystemContext *SystemContext::getInstance(void) {
    static SystemContext *SINGLETON = new SystemContext();
    return SINGLETON;
}

SystemContext::SystemContext(void) : scheduler(new EventSchedulerImpl()) {
    this->scheduler->init();
}

SystemContext::~SystemContext(void) {
    delete this->scheduler;
}

void SystemContext::run(void) {
    const unsigned long int t0 = millis();
    this->scheduler->step();
    delay(PERIOD - (millis() - t0));
}
