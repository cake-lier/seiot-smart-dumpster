/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "SystemContext.h"
#include "src/controller/ControllerImpl.h"
#include "GlobalConstants.h"
#include <Arduino.h>

SystemContext *SystemContext::SINGLETON = nullptr;

SystemContext *SystemContext::getInstance(void) {
    return SINGLETON;
}

SystemContext::SystemContext(void) : controller(new ControllerImpl()) {}

SystemContext::~SystemContext(void) {
    delete this->controller;
}

void SystemContext::run(void) {
    const unsigned long int t0 = millis();
    this->controller->run();
    delay(PERIOD - (millis() - t0));
}

void SystemContext::init(void) {
    if (SINGLETON == nullptr) {
        SINGLETON = new SystemContext();
    }
}
