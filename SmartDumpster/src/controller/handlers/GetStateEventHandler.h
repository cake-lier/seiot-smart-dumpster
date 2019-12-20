/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __GET_STATE_EVENT_HANDLER__
#define __GET_STATE_EVENT_HANDLER__

#include "AbstractEventHandler.h"
#include "../../model/service/Service.h"

/*
 * 
 */
class GetStateEventHandler: public AbstractEventHandler { 
    public:
        /*
         * 
         */
        GetStateEventHandler(const Service &service, const bool &isAvailable);
        /*
         * Default destructor.
         */
        ~GetStateEventHandler(void);
        /*
         * 
         */
        void execute(void) const override;
    private:
        const Service &service;
        const bool &isAvailable;
};

#endif
