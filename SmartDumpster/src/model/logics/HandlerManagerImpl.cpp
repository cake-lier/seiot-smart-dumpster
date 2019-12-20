#include "HandlerManagerImpl.h"

HandlerManagerImpl::HandlerManagerImpl(PhysicalSystem *system, unsigned int *openTime) {
    this->physicalSystem = system;
    this->openTime = openTime;
}

void HandlerManagerImpl::runEventHandler(const Event event) {
    switch(event) {
        case Event::SET_TRASH_A: this->physicalSystem->turnOnTrashALed(); break;
        case Event::SET_TRASH_B: this->physicalSystem->turnOnTrashBLed(); break;
        case Event::SET_TRASH_C: this->physicalSystem->turnOnTrashCLed(); break;
        case Event::START_DEPOSIT: this->physicalSystem->openServo(); break;
        case Event::END_DEPOSIT: this->physicalSystem->closeServo(); this->physicalSystem->turnOffActiveTrashLed(); break;
        case Event::KEEP_OPEN_REQUEST: *(this->openTime) = 0; break;
        default: ;
    }
}