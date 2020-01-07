#include "HandlerManagerImpl.h"

HandlerManagerImpl::HandlerManagerImpl(PhysicalSystem *system, CommunicationSystem *commSystem, unsigned int *openTime) {
    this->physicalSystem = system;
    this->openTime = openTime;
    this->commSystem = commSystem;
}

void HandlerManagerImpl::runEventHandler(const Event event) {
    switch(event) {
        case Event::SET_TRASH_A: 
            this->physicalSystem->turnOnTrashALed(); 
            break;
        case Event::SET_TRASH_B: 
            this->physicalSystem->turnOnTrashBLed(); 
            break;
        case Event::SET_TRASH_C: 
            this->physicalSystem->turnOnTrashCLed();
            break;
        case Event::START_DEPOSIT: 
            *(this->openTime) = 0;
            this->physicalSystem->openServo();
            this->commSystem->sendMessage(Message::START_DEPOSIT);
            break;
        case Event::END_DEPOSIT:
            *(this->openTime) = 0;
            this->physicalSystem->closeServo();
            this->physicalSystem->turnOffActiveTrashLed();
            this->commSystem->sendMessage(Message::END_DEPOSIT);
            break;
        case Event::KEEP_OPEN_REQUEST: 
            *(this->openTime) = 0;
            break;
        default: ;
    }
}