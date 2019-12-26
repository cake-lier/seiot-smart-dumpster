/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __START_DEPOSIT_EVENT_HANDLER__
#define __START_DEPOSIT_EVENT_HANDLER__

#include "../../controller/handler/AbstractEventHandler.h"
#include "../service/Service.h"

/*
 * 
 */
class StartDepositEventHandler: public AbstractEventHandler { 
    public:
        /*
         * 
         */
        StartDepositEventHandler(const Service &service, const bool &isAvailable, bool &isWeightPolling);
        /*
         * Default destructor.
         */
        ~StartDepositEventHandler(void);
        /*
         * 
         */
        void execute(void) const override;
    private:
        const Service &service;
        const bool &isAvailable;
        bool &isWeightPolling;
};

#endif
