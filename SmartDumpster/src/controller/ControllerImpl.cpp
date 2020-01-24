/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "ControllerImpl.h"
#include "../model/communication/CommunicationSystemImpl.h"
#include "../model/physics/PhysicalSystemImpl.h"
#include "../model/logics/HandlerManagerImpl.h"
#include "../model/logics/EventGeneratorImpl.h"

using namespace std;

ControllerImpl::ControllerImpl(void) : physicalSystem(new PhysicalSystemImpl()),
                                       commSystem(new CommunicationSystemImpl()), 
                                       handlerManager(new HandlerManagerImpl(*this->physicalSystem,
                                                                             *this->commSystem,
                                                                             this->openCount)),
                                       eventGenerator(new EventGeneratorImpl()) {
    this->openCount = 0;
}

ControllerImpl::~ControllerImpl(void) {
    delete this->physicalSystem;
    delete this->commSystem;
    delete this->handlerManager;
    delete this->eventGenerator;
}

void ControllerImpl::run(void) {
    if (this->physicalSystem->isServoOpen()) {
       this->openCount++;
    }
    this->handlerManager->runEventHandler(this->eventGenerator->generateEventFromMessage(this->commSystem->receiveMessage()));
    auto events = this->eventGenerator->generatePeriodicEvents(this->openCount);
    for_each(events->begin(), events->end(), [&](const Event event) -> void {
        this->handlerManager->runEventHandler(event);
    });
    delete events;
}