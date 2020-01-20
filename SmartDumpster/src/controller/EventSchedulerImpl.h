/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __EVENT_SCHEDULER_IMPL__
#define __EVENT_SCHEDULER_IMPL__

#include "EventScheduler.h"
#include "../model/logics/EventHandlerManager.h"
#include "../model/physics/PhysicalSystem.h"
#include "../model/service/Service.h"

/*
 * A class used to execute a step of the system life.
 */
class EventSchedulerImpl: public EventScheduler { 
    public:
        /*
         * Default constructor.
         */
        EventSchedulerImpl(void);
        /*
         * Default destructor.
         */
        ~EventSchedulerImpl(void);
        /*
         * Executes a step.
         */
        void step(void) override;
    private:
        PhysicalSystem * const physics;
        Service * const service;
        bool isAvailable;
        bool isWeightPolling;
        int currentWeight;
        EventHandlerManager * const manager;
};

#endif
