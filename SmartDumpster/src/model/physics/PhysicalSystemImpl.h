/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __P_SYSTEM_IMPL__
#define __P_SYSTEM_IMPL__

#include "PhysicalSystem.h"
#include "Led.h"
#include "Potentiometer.h"

/*
 * The container class for the physical components, sensors and actuators, which make up the system controlled by the
 * Arduino. It should expose methods to the general system so as to let it use the physical components in the only way
 * required to fulfill its duty.
 */
class PhysicalSystemImpl : public PhysicalSystem {
    public:
        /*
         * Default constructor.
         */
        PhysicalSystemImpl(void);
        /*
         * Default destructor.
         */
        ~PhysicalSystemImpl(void);
        /*
         * It turns on the "available" led.
         */
        void turnOnAvailableLed(void);
        /*
         * It turns off the "available" led.
         */
        void turnOffAvailableLed(void);
        /*
         * It returns if the "available" led is currently on or not.
         */
        bool isOnAvailableLed(void) const;
        /*
         * It turns on the "not available" led.
         */
        void turnOnNotAvailableLed(void);
        /*
         * It turns off the "not available" led.
         */
        void turnOffNotAvailableLed(void);
        /*
         * It returns if the "not available" led is currently on or not.
         */
        bool isOnNotAvailableLed(void) const;
        /*
         * It returns the weight of the trash put into the dumpster as simulated by the potentiometer.
         */
        int getWeight(void) const;
    private:
        Led *availableLed;
        Led *notAvailableLed;
        Potentiometer *potentiometer;
};

#endif
