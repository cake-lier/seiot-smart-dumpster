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
         * It turns on the led of the trash type A.
         */
        virtual void turnOnTrashALed(void) = 0;
        /*
         * It turns on the led of the trash type B.
         */
        virtual void turnOnTrashBLed(void) = 0;
        /*
         * It turns on the led of the trash type C.
         */
        virtual void turnOnTrashCLed(void) = 0;
        /*
         * It turns off the active led.
         */
        virtual void turnOffActiveTrashLed() = 0;
        /*
         * It moves the servo to 180°.
         */
        virtual void openServo(void) = 0;
        /*
         * It moves the servo to 0°.
         */
        virtual void closeServo(void) = 0;
        /*
         * Default destructor.
         */
        virtual ~PhysicalSystem(void) {}
        /*
         * Returns whether the servo is open or not.
         */
        virtual bool isServoOpen(void) = 0;
};

#endif
