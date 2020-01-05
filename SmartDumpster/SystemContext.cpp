/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "SystemContext.h"
#include "src/controller/ControllerImpl.h"

SystemContext *SystemContext::SINGLETON = nullptr;

SystemContext *SystemContext::getInstance(void) {
    return SINGLETON;
}

SystemContext::SystemContext(SoftwareSerial *btc) {
    this->controller = new ControllerImpl(btc);
}

SystemContext::~SystemContext(void) {
    delete this->controller;
}

void SystemContext::run(void) {
    this->controller->run();
}

void SystemContext::init(SoftwareSerial *btc) {
    if (SINGLETON == nullptr) {
        SINGLETON = new SystemContext(btc);
    }
}
