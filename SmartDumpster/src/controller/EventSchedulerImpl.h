/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __EVENT_SCHEDULER_IMPL__
#define __EVENT_SCHEDULER_IMPL__

#include "EventScheduler.h"
#include "EventHandlerManager.h"
#include "../model/physics/PhysicalSystem.h"
#include "../model/service/Service.h"

/*
 * 
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
         * 
         */
        void init(void) override;
        /*
         * 
         */
        void step(void) override;
    private:
        EventHandlerManager * const manager;
        PhysicalSystem * const physics;
        Service * const service;
        bool isAvailable;
        bool isWeightPolling;
        int currentWeight;
};

#endif
