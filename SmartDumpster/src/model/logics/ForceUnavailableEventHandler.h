/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __FORCE_UNAVAILABLE_EVENT_HANDLER__
#define __FORCE_UNAVAILABLE_EVENT_HANDLER__

#include "../../controller/handler/AbstractEventHandler.h"
#include "../physics/PhysicalSystem.h"
#include "../service/Service.h"

/*
 * 
 */
class ForceUnavailableEventHandler: public AbstractEventHandler { 
    public:
        /*
         * 
         */
        ForceUnavailableEventHandler(PhysicalSystem &physics, const Service &service, bool &isAvailable);
        /*
         * Default destructor.
         */
        ~ForceUnavailableEventHandler(void);
        /*
         * 
         */
        void execute(void) const override;
    private:
        PhysicalSystem &physics;
        const Service &service;
        bool &isAvailable;
};

#endif
