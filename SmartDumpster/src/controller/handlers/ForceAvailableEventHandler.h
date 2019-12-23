/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __FORCE_AVAILABLE_EVENT_HANDLER__
#define __FORCE_AVAILABLE_EVENT_HANDLER__

#include "AbstractEventHandler.h"
#include "../../model/physics/PhysicalSystem.h"
#include "../../model/service/Service.h"

/*
 * 
 */
class ForceAvailableEventHandler: public AbstractEventHandler { 
    public:
        /*
         * 
         */
        ForceAvailableEventHandler(PhysicalSystem &physics, const Service &service, bool &isAvailable, int &currentWeight);
        /*
         * Default destructor.
         */
        ~ForceAvailableEventHandler(void);
        /*
         * 
         */
        void execute(void) const override;
    private:
        PhysicalSystem &physics;
        const Service &service;
        bool &isAvailable;
        int &currentWeight;
};

#endif
