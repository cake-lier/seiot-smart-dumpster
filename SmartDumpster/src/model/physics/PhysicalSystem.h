/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __P_SYSTEM__
#define __P_SYSTEM__

/*
 * The container class for the physical components, sensors and actuators, which make up the system controlled by the
 * Arduino. It should expose methods to the general system so as to let it use the physical components in the only way
 * required to fulfill its duty.
 */
class PhysicalSystem {
    public:
        /*
         * It turns on the "available" led.
         */
        virtual void turnOnAvailableLed(void) = 0;
        /*
         * It turns off the "available" led.
         */
        virtual void turnOffAvailableLed(void) = 0;
        /*
         * It turns on the "not available" led.
         */
        virtual void turnOnNotAvailableLed(void) = 0;
        /*
         * It turns off the "not available" led.
         */
        virtual void turnOffNotAvailableLed(void) = 0;
        /*
         * It returns the weight of the trash put into the dumpster as simulated by the potentiometer.
         */
        virtual int getWeight(void) const = 0;
        /*
         * Default destructor.
         */
        virtual ~PhysicalSystem(void) {}
};

#endif
