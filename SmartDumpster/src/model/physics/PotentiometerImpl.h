/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __POTENTIOMETER_IMPL__
#define __POTENTIOMETER_IMPL__

#include "Potentiometer.h"

/*
 * It represents a potentiometer, a variable resistor which can be rotated so as to change its resistance in the circuit
 * to which is wired. It can be used as a sensor for a value put between two extremes, corresponding to the extremes of
 * rotation of the potentiometer.
 */
class PotentiometerImpl : public Potentiometer {
    public:
        /*
         * Constructor which asks for the Arduino pin to which this potentiometer is currently attached.
         */
        PotentiometerImpl(const int pin);
        /*
         * Default destructor.
         */
        ~PotentiometerImpl(void);
        /*
         * It reads the current value of the potentiometer as a number between two extreme values provided to this
         * method.
         */
        int readMappedValue(const int min, const int max) const override;
    private:
        int pin;
};

#endif
