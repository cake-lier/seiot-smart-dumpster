/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "SystemContext.h"
#include "src/controller/ControllerImpl.h"

SystemContext *SystemContext::SINGLETON = nullptr;

SystemContext *SystemContext::getInstance(void) {
    return SINGLETON;
}

SystemContext::SystemContext(void) {
    this->controller = new ControllerImpl();
}

SystemContext::~SystemContext(void) {
    delete this->controller;
}

void SystemContext::run(void) {
    this->controller->run();
}

void SystemContext::init(void) {
    if (SINGLETON == nullptr) {
        SINGLETON = new SystemContext();
    }
}
