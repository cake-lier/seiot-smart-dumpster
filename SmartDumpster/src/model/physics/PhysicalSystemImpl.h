/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __P_SYSTEM_IMPL__
#define __P_SYSTEM_IMPL__

#include <vector>
#include "PhysicalSystem.h"
#include "Led.h"
#include "Button.h"
#include "Pir.h"
#include "Radar.h"
#include "Potentiometer.h"

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
         * It turns on the alarm led.
         */
        void turnOnAlarmLed(void) override;
        /*
         * It turns off the alarm led.
         */
        void turnOffAlarmLed(void) override;
        /*
         * It returns if the alarm led is currently on or not.
         */
        bool isOnAlarmLed(void) const override;
        /*
         * It turns on the led used when a presence is detected.
         */
        void turnOnPresenceDetectedLed(void) override;
        /*
         * It turns off the led used when a presence is detected.
         */
        void turnOffPresenceDetectedLed(void) override;
        /*
         * It returns if the led used when a presence is detected is currently on or not.
         */
        bool isOnPresenceDetectedLed(void) const override;
        /*
         * It returns if the push-button for changing the system to the first mode (single) is currently pressed.
         */
        bool isTm1Pressed(void) const override;
        /*
         * It returns if the push-button for changing the system to the second mode (manual) is currently pressed.
         */
        bool isTm2Pressed(void) const override;
        /*
         * It returns if the push-button for changing the system to the third mode (auto) is currently pressed.
         */
        bool isTm3Pressed(void) const override;
        /*
         * It returns if the PIR sensor is currently detecting something or not.
         */
        bool isPirDetecting(void) const override;
        /*
         * It moves the radar one step to the left to the previous slice of its field of view.
         */
        void moveRadarLeft(void) override;
        /*
         * It moves the radar one step to the right to the next slice of its field of view.
         */
        void moveRadarRight(void) override;
        /*
         * It resets the position of the radar to the slice of its field of view corresponding to 0 degrees.
         */
        void moveRadarHome(void) override;
        /*
         * It returns the current position of the radar in degrees.
         */
        int getRadarPosition(void) const override;
        /*
         * It returns the distance between the radar and the nearest object in its current line of sight.
         */
        float getRadarDistance(void) const override;
        /*
         * It returns the time a scan should need to complete as read by the potentiometer.
         */
        int getScanTime(void) const override;
        /*
         * It puts the whole physical system to sleep. Given the nature of the sleep mode, the system can be woken up 
         * only with a message on the serial console or with an external interrupt from the PIR sensor or a pression 
         * of TM2 or TM3.
         */
        void sleep(void) override;
        /*
         * It registers a new listener to the PIR sensor so as let it be notified when the sensor is detecting a moving
         * object.
         */
        void registerPirListener(PirListener *listener) override;
        /*
         * It registers a new listener to push-button pressures, so as to let it be notified when a button is pressed
         * during sleep.
         */
        void registerButtonListener(ButtonListener *listener) override;
        /*
         * The action to be performed when the physical systems wakes up thanks to a signal from the pir. It needs to be
         * a static method because it should be called by the interrupt routine for waking up the sistem.
         */
        static void onPirWakeUp(void);
        /*
         * The action to be performed when the physical systems wakes up thanks to a pression on TM2. It needs to be a
         * static method because it should be called by the interrupt routine for waking up the sistem.
         */
        static void onTm2WakeUp(void);
        /*
         * The action to be performed when the physical systems wakes up thanks to a pression on TM3. It needs to be a
         * static method because it should be called by the interrupt routine for waking up the sistem.
         */
        static void onTm3WakeUp(void);
    private:
        /* 
         * Disable all possible interrupts, which could be caused by buttons or by a PIR sensor.
         */
        static void disableInterrupts(void);
        Led *alarmLed;
        Led *presenceDetectedLed;
        Button *tm1;
        Button *tm2;
        Button *tm3;
        Potentiometer *potentiometer;
        Pir *pir;
        Radar *radar;
        static vector<PirListener *> pirListeners;
        static vector<ButtonListener *> buttonListeners;
};

#endif
