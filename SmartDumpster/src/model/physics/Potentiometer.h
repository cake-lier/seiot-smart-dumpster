/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__

/*
 * It represents a potentiometer, a variable resistor which can be rotated so as to change its resistance in the circuit
 * to which is wired. It can be used as a sensor for a value put between two extremes, corresponding to the extremes of
 * rotation of the potentiometer.
 */
class Potentiometer {
    public:
        /*
         * It reads the current value of the potentiometer as a number between two extreme values provided to this
         * method.
         */
        virtual int readMappedValue(const int min, const int max) const = 0;
        /*
         * Default destructor.
         */
        virtual ~Potentiometer(void) {}
};

#endif
