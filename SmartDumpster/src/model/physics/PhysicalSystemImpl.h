/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __P_SYSTEM_IMPL__
#define __P_SYSTEM_IMPL__

#include "PhysicalSystem.h"
#include "Led.h"
#include "ServoMotor.h"

using namespace std;

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
         * It turns on the led of the trash type A.
         */
        void turnOnTrashALed(void) override;
        /*
         * It turns on the led of the trash type B.
         */
        void turnOnTrashBLed(void) override;
        /*
         * It turns on the led of the trash type C.
         */
        void turnOnTrashCLed(void) override;
        /*
         * It turns off the active led.
         */
        void turnOffActiveTrashLed() override;
        /*
         * It moves the servo to 180°.
         */
        void openServo(void) override;
        /*
         * It moves the servo to 0°.
         */
        void closeServo(void) override;
    private:
        Led *trashLedA;
        Led *trashLedB;
        Led *trashLedC;
        ServoMotor *servo;
        Led *activeLed;
};

#endif
