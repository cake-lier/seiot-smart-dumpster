#ifndef __CONTROLLER_IMPL__
#define __CONTROLLER_IMPL__

#include "../model/physics/PhysicalSystem.h"
#include "../model/communication/CommunicationSystem.h"
#include "../model/logics/HandlerManager.h"
#include "../model/logics/EventGenerator.h"
#include "Controller.h"
#include <SoftwareSerial.h>

class ControllerImpl : public Controller {
    public:
        ControllerImpl(SoftwareSerial *btc);
        ~ControllerImpl(void);
        void run(void) override;
    private:
        PhysicalSystem *physicalSystem;
        CommunicationSystem *commSystem;
        HandlerManager *handlerManager;
        EventGenerator *eventGenerator;
        unsigned int openTime;
        unsigned int lastCheckedTime;
};

#endif