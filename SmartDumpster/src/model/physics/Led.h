/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __LIGHT__
#define __LIGHT__

/*
 * It represents a Light Emitting Diode which could be turned on or off.
 */
class Led { 
    public:
        /*
         * It turns on the led.
         */
        virtual void switchOn(void) = 0;
        /*
         * It turns off the led.
         */
        virtual void switchOff(void) = 0;
        /*
         * It asks to the led its current status, if it has been turned on or not.
         */
        virtual bool isOn(void) const = 0;
        /*
         * Default destructor.
         */
        virtual ~Led(void) {}
};

#endif
