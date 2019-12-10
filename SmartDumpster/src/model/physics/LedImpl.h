/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __LED__
#define __LED__

#include "Led.h"

/*
 * It represents a Light Emitting Diode which could be turned on or off.
 */
class LedImpl : public Led { 
    public:
        /*
         * Constructor which asks for the Arduino pin to which this led is wired.
         */
        LedImpl(const int pin);
        /*
         * Default destructor.
         */
        ~LedImpl(void);
        /*
         * It turns on the led.
         */
        void switchOn(void) override;
        /*
         * It turns off the led.
         */
        void switchOff(void) override;
        /*
         * It asks to the led its current status, if it has been turned on or not.
         */
        bool isOn(void) const override;
    private:
       int pin;
       bool on;
};

#endif
