/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __P_SYSTEM__
#define __P_SYSTEM__

#include "PirListener.h"
#include "ButtonListener.h"

#define TM3_BUTTON_CODE 3
#define TM2_BUTTON_CODE 2

/*
 * The container class for the physical components, sensors and actuators, which make up the system controlled by the
 * Arduino. It should expose methods to the general system so as to let it use the physical components in the only way
 * required to fulfill its duty.
 */
class PhysicalSystem {
    public:
        /*
         * It turns on the alarm led.
         */
        virtual void turnOnAlarmLed(void) = 0;
        /*
         * It turns off the alarm led.
         */
        virtual void turnOffAlarmLed(void) = 0;
        /*
         * It returns if the alarm led is currently on or not.
         */
        virtual bool isOnAlarmLed(void) const = 0;
        /*
         * It turns on the led used when a presence is detected.
         */
        virtual void turnOnPresenceDetectedLed(void) = 0;
        /*
         * It turns off the led used when a presence is detected.
         */
        virtual void turnOffPresenceDetectedLed(void) = 0;
        /*
         * It returns if the led used when a presence is detected is currently on or not.
         */
        virtual bool isOnPresenceDetectedLed(void) const = 0;
        /*
         * It returns if the push-button for changing the system to the first mode (single) is currently pressed.
         */
        virtual bool isTm1Pressed(void) const = 0;
        /*
         * It returns if the push-button for changing the system to the second mode (manual) is currently pressed.
         */
        virtual bool isTm2Pressed(void) const = 0;
        /*
         * It returns if the push-button for changing the system to the third mode (auto) is currently pressed.
         */
        virtual bool isTm3Pressed(void) const = 0;
        /*
         * It returns if the PIR sensor is currently detecting something or not.
         */
        virtual bool isPirDetecting(void) const = 0;
        /*
         * It moves the radar one step to the left to the previous slice of its field of view.
         */
        virtual void moveRadarLeft(void) = 0;
        /*
         * It moves the radar one step to the right to the next slice of its field of view.
         */
        virtual void moveRadarRight(void) = 0;
        /*
         * It resets the position of the radar to the slice of its field of view corresponding to 0 degrees.
         */
        virtual void moveRadarHome(void) = 0;
        /*
         * It returns the current position of the radar in degrees.
         */
        virtual int getRadarPosition(void) const = 0;
        /*
         * It returns the distance between the radar and the nearest object in its current line of sight.
         */
        virtual float getRadarDistance(void) const = 0;
        /*
         * It returns the time a scan should need to complete as read by the potentiometer.
         */
        virtual int getScanTime(void) const = 0;
        /*
         * It puts the whole physical system to sleep.
         */
        virtual void sleep(void) = 0;
        /*
         * It registers a new listener to the PIR sensor so as let it be notified when the sensor is detecting a moving
         * object.
         */
        virtual void registerPirListener(PirListener *listener) = 0;
        /*
         * It registers a new listener to button pressions, so as to let it be notified when a button is pressed during sleep.
         */
        virtual void registerButtonListener(ButtonListener *listener) = 0;
        /*
         * Default destructor.
         */
        virtual ~PhysicalSystem(void) {}
};

#endif
