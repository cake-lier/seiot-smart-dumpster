/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __HANDLER_MANAGER_IMPL__
#define __HANDLER_MANAGER_IMPL__

#include "HandlerManager.h"
#include "../physics/PhysicalSystem.h"
#include "../communication/CommunicationSystem.h"
#include "EventHandler.h"
#include <vector>

using namespace std;

/*
 * The class which has the responsibility of managing the handlers which have to be executed while this software is executing.
 * It can add a new event handler to the list of the already inserted ones or executing all the handlers which are bind to a
 * specified event that has happened.
 */
class HandlerManagerImpl : public HandlerManager {
    public:
        /*
         * Constructor which takes a reference to the physical system of the global system, a reference to the communication
         * system and a reference to the counter of the time elapsed from the beginning of the last deposit.
         */
        HandlerManagerImpl(PhysicalSystem &system, const CommunicationSystem &commSystem, unsigned int &openCount);
        /*
         * Default destructor.
         */
        ~HandlerManagerImpl(void);
        /*
         * It executes all the event handlers tied to the passed event.
         */
        void runEventHandler(const Event event) const override;
        /*
         * It adds a new event handler to the list of the already inserted ones.
         */
        void addEventHandler(const EventHandler * const handler) const override;
    private:
        PhysicalSystem &physicalSystem;
        const CommunicationSystem &commSystem;
        unsigned int &openCount;
        vector<const EventHandler *> * const handlers;
};

#endif