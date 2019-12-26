/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __END_DEPOSIT_EVENT_HANDLER__
#define __END_DEPOSIT_EVENT_HANDLER__

#include "../../controller/handler/AbstractEventHandler.h"
#include "../service/Service.h"
#include "../physics/PhysicalSystem.h"

/*
 * 
 */
class EndDepositEventHandler: public AbstractEventHandler { 
    public:
        /*
         * 
         */
        EndDepositEventHandler(PhysicalSystem &physics,
                               const Service &service,
                               bool &isAvailable,
                               bool &isWeightPolling,
                               int &currentWeight);
        /*
         * Default destructor.
         */
        ~EndDepositEventHandler(void);
        /*
         * 
         */
        void execute(void) const override;
    private:
        PhysicalSystem &physics;
        const Service &service;
        int &currentWeight;
        bool &isAvailable;
        bool &isWeightPolling;
};

#endif
