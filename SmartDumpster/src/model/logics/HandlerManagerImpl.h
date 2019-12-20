#ifndef __HANDLER_MANAGER_IMPL__
#define __HANDLER_MANAGER_IMPL__

#include "HandlerManager.h"
#include "../physics/PhysicalSystem.h"
#include "../communication/CommunicationSystem.h"

class HandlerManagerImpl : public HandlerManager {
    public:
        /*
         * Default constructor.
         */
        HandlerManagerImpl(PhysicalSystem *system, CommunicationSystem *commSystem, unsigned int *openTime);
        /*
         * Default destructor.
         */
        ~HandlerManagerImpl() {}
        /*
         * 
         */
        void runEventHandler(Event) override;
    private:
        PhysicalSystem *physicalSystem;
        CommunicationSystem *commSystem;
        unsigned int *openTime;
};

#endif