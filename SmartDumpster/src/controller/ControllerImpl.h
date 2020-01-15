/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __CONTROLLER_IMPL__
#define __CONTROLLER_IMPL__

#include "../model/physics/PhysicalSystem.h"
#include "../model/communication/CommunicationSystem.h"
#include "../model/logics/HandlerManager.h"
#include "../model/logics/EventGenerator.h"
#include "Controller.h"

/*
 * The root class of the controller component of this software, it has the job of coordinating the use of all model elements so
 * as to put into execution its logic.
 */
class ControllerImpl : public Controller {
    public:
        /*
         * Default constructor.
         */
        ControllerImpl(void);
        /*
         * Default destructor.
         */
        ~ControllerImpl(void);
        /*
         * It runs one iteration of the loop that executes the application.
         */
        void run(void) override;
    private:
        PhysicalSystem * const physicalSystem;
        const CommunicationSystem * const commSystem;
        HandlerManager * const handlerManager;
        const EventGenerator * const eventGenerator;
        unsigned int openCount;
};

#endif