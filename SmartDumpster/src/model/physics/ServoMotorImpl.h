/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __SERVO_MOTOR_IMPL__
#define __SERVO_MOTOR_IMPL__

#include "ServoMotor.h"
#include <Servo.h>

/*
 * It represents a servomotor, a linear actuator that can rotate to a precise angle upon command in the interval
 * between 0 and 180.
 */
class ServoMotorImpl : public ServoMotor {
    public:
        /*
         * Constructor which takes the Arduino pin to which the servomotor is attached.
         */
        ServoMotorImpl(const int pin);
        /*
         * Default destructor.
         */
        ~ServoMotorImpl(void);
        /*
         * It moves the servomotor to a specific angle by receiving its magnitude in degrees. Not all angles can be
         * reached, especially the non-integer ones. The user can specify a non-integer degree anyway, the servomotor
         * will try to position itself to the angle as closely as possible.
         */
        void moveToDegree(const float degrees);
        /*
         * It returns the current position of the servomotor in degrees. Initially, before the user positions the
         * servomotor to any angle, it can't know at which angle is positioned. During this phase, the servomotor
         * will return an error value if asked at which angle is positioned.
         */
        int getCurrentDegree(void) const;
        /*
         * It turns on the servomotor.
         */
        void turnOn(void);
        /*
         * It turns off the servomotor.
         */
        void turnOff(void);
    private:
        Servo *motor;
        int pin;
        int currentDegree;
};

#endif
