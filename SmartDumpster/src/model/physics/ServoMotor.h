/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

/*
 * It represents a servomotor, a linear actuator that can rotate to a precise angle upon command in the interval
 * between 0 and 180.
 */
class ServoMotor {
    public:
        /*
         * It moves the servomotor to a specific angle by receiving its magnitude in degrees. Not all angles can be
         * reached, especially the non-integer ones. The user can specify a non-integer degree anyway, the servomotor
         * will try to position itself to the angle as closely as possible.
         */
        virtual void moveToDegree(const float degrees) = 0;
        /*
         * It returns the current position of the servomotor in degrees. Initially, before the user positions the
         * servomotor to any angle, it can't know at which angle is positioned. During this phase, the servomotor
         * will return an error value if asked at which angle is positioned.
         */
        virtual int getCurrentDegree(void) const = 0;
        /*
         * It turns on the servomotor.
         */
        virtual void turnOn(void) = 0;
        /*
         * It turns off the servomotor.
         */
        virtual void turnOff(void) = 0;
        /*
         * Default destructor.
         */
        virtual ~ServoMotor(void) {}
};

#endif
