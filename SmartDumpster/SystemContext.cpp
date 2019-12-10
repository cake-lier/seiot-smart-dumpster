/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "SystemContext.h"
#include "src/model/console/ConsoleImpl.h"
#include "src/model/physics/PhysicalSystemImpl.h"
#include "src/controller/SchedulerImpl.h"
#include "src/model/logics/CheckChangeModeTask.h"
#include "src/model/logics/ManualModeTask.h"
#include "src/model/logics/SingleModeTask.h"
#include "src/model/logics/AutoModeTask.h"
#include <Arduino.h>

#define WARM_UP_TIME 1000UL   // milliseconds
#define PERIOD 125UL          // milliseconds

SystemContext *SystemContext::SINGLETON = nullptr;

SystemContext *SystemContext::getInstance(void) {
    return SINGLETON;
}

SystemContext::SystemContext(void) {
    this->systemState = SystemState::MANUAL_MODE;
    this->physicalSystem = new PhysicalSystemImpl();
    this->scheduler = new SchedulerImpl();
    this->console = new ConsoleImpl();
    this->scheduler->addTask(new CheckChangeModeTask(&systemState, physicalSystem, console));
    this->scheduler->addTask(new ManualModeTask(&systemState, physicalSystem, console));
    this->scheduler->addTask(new SingleModeTask(&systemState, physicalSystem, console));
    this->scheduler->addTask(new AutoModeTask(&systemState, physicalSystem, console));
    for (int i = 0; i < 10; i++)  {
        delay(WARM_UP_TIME); // calibrating pir
    }
}

SystemContext::~SystemContext(void) {
    delete this->physicalSystem;
    delete this->scheduler;
    delete this->console;
}

void SystemContext::run(void) {
    const unsigned long int t0 = millis();
    this->scheduler->schedule();
    delay(PERIOD - (millis() - t0));
}

void SystemContext::init(void) {
    if (SINGLETON == nullptr) {
        SINGLETON = new SystemContext();
    }
}
