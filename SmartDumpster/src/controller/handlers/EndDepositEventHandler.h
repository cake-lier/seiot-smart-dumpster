/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __END_DEPOSIT_EVENT_HANDLER__
#define __END_DEPOSIT_EVENT_HANDLER__

#include "AbstractEventHandler.h"
#include "../../model/service/Service.h"

/*
 * 
 */
class EndDepositEventHandler: public AbstractEventHandler { 
    public:
        /*
         * 
         */
        EndDepositEventHandler(const Service &service, bool &isAvailable, bool &isWeightPolling, const int &currentWeight);
        /*
         * Default destructor.
         */
        ~EndDepositEventHandler(void);
        /*
         * 
         */
        void execute(void) const override;
    private:
        const Service &service;
        const int &currentWeight;
        bool &isAvailable;
        bool &isWeightPolling;
};

#endif
