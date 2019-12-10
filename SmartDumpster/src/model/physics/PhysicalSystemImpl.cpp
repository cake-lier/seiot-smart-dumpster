/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "PhysicalSystemImpl.h"
#include "LedImpl.h"
#include "ButtonImpl.h"
#include "PirImpl.h"
#include "RadarImpl.h"
#include "PotentiometerImpl.h"
#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <algorithm>
#include <avr/interrupt.h>

/* pins */
#define POT_PIN A0
#define PIR_PIN 2
#define LA_PIN 5
#define LD_PIN 6
#define ECHO_PIN 7
#define TRIG_PIN 8
#define SERVO_PIN 9
#define TM1_PIN 11 // to single
#define TM2_PIN 3 // to manual
#define TM3_PIN 13 // to auto
/* constants */
#define N 16
#define STEP_DEGREES (180.0F / N)
#define PERIOD 125UL                // milliseconds
#define T_MIN 2                     // seconds
#define T_MAX 10                    // seconds

vector<PirListener *> PhysicalSystemImpl::pirListeners = vector<PirListener *>();
vector<ButtonListener *> PhysicalSystemImpl::buttonListeners = vector<ButtonListener *>();

PhysicalSystemImpl::PhysicalSystemImpl(void) {
    this->alarmLed = new LedImpl(LA_PIN);
    this->presenceDetectedLed = new LedImpl(LD_PIN);
    this->tm1 = new ButtonImpl(TM1_PIN);
    this->tm2 = new ButtonImpl(TM2_PIN);
    this->tm3 = new ButtonImpl(TM3_PIN);
    this->potentiometer = new PotentiometerImpl(POT_PIN);
    this->pir = new PirImpl(PIR_PIN);
    this->radar = new RadarImpl(ECHO_PIN, TRIG_PIN, SERVO_PIN);
}

PhysicalSystemImpl::~PhysicalSystemImpl(void) {
    delete this->alarmLed;
    delete this->presenceDetectedLed;
    delete this->tm1;
    delete this->tm2;
    delete this->tm3;
    delete this->potentiometer;
    delete this->pir;
    delete this->radar;
}

void PhysicalSystemImpl::turnOnAlarmLed(void) {
    this->alarmLed->switchOn();
}

void PhysicalSystemImpl::turnOffAlarmLed(void) {
    this->alarmLed->switchOff();
}

bool PhysicalSystemImpl::isOnAlarmLed(void) const {
    return this->alarmLed->isOn();
}

void PhysicalSystemImpl::turnOnPresenceDetectedLed(void) {
    this->presenceDetectedLed->switchOn();
}

void PhysicalSystemImpl::turnOffPresenceDetectedLed(void) {
    this->presenceDetectedLed->switchOff();
}

bool PhysicalSystemImpl::isOnPresenceDetectedLed(void) const {
    return this->presenceDetectedLed->isOn();
}

bool PhysicalSystemImpl::isTm1Pressed(void) const {
    return this->tm1->isPressed();
}

bool PhysicalSystemImpl::isTm2Pressed(void) const {
    return this->tm2->isPressed();
}

bool PhysicalSystemImpl::isTm3Pressed(void) const {
    return this->tm3->isPressed();
}

bool PhysicalSystemImpl::isPirDetecting(void) const {
    return this->pir->isPresenceDetected();
}

void PhysicalSystemImpl::moveRadarLeft(void) {
    this->radar->stepLeft(STEP_DEGREES);
}

void PhysicalSystemImpl::moveRadarRight(void) {
    this->radar->stepRight(STEP_DEGREES);
}

void PhysicalSystemImpl::moveRadarHome(void) {
    this->radar->resetPosition();
}

int PhysicalSystemImpl::getRadarPosition(void) const {
    return this->radar->getCurrentPosition();
}

float PhysicalSystemImpl::getRadarDistance(void) const {
    return this->radar->getDistance();
}

int PhysicalSystemImpl::getScanTime(void) const {
    return this->potentiometer->readMappedValue(T_MIN, T_MAX);
}

void PhysicalSystemImpl::sleep(void) {
    /* enable change to auto mode */
    /* clears possible interrupts received from the button during use */
    PCIFR = _BV(PCIF0);
    /* enable pin change interrupts for pins on port B (PCINT0 to PCINT7), equivalent to PCICR  |= 0b0000001; */
    *digitalPinToPCICR(TM3_PIN) |= (1<<digitalPinToPCICRbit(TM3_PIN));
    /* enable the interrupts for pin 13, equivalent to PCMSK0 |= bit (PCINT5); */
    *digitalPinToPCMSK(TM3_PIN) |= (1<<digitalPinToPCMSKbit(TM3_PIN));
    /* enable change to manual mode */
    /* clears possible interrupts received from the button during use */
    EIFR = _BV(INTF1);
    attachInterrupt(digitalPinToInterrupt(TM2_PIN), onTm2WakeUp, HIGH);
    /* enable pir */
    /* clears possible interrupts received from the pir during use */
    EIFR = _BV(INTF0);
    attachInterrupt(digitalPinToInterrupt(PIR_PIN), onPirWakeUp, HIGH);
    /* setting sleep mode and disabling possible interrupt causes */
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();
    power_adc_disable();
    power_spi_disable();
    power_timer0_disable();
    power_timer1_disable();
    power_timer2_disable();
    power_twi_disable();
    sleep_cpu(); /* sleep */
    sleep_disable(); /* First thing to do is disable sleep. */
    power_all_enable();
}

void PhysicalSystemImpl::registerPirListener(PirListener *listener) {
    pirListeners.push_back(listener);
}

void PhysicalSystemImpl::registerButtonListener(ButtonListener *listener) {
    buttonListeners.push_back(listener);
}

void PhysicalSystemImpl::onPirWakeUp(void) {
    PhysicalSystemImpl::disableInterrupts();
    for_each(pirListeners.begin(), pirListeners.end(), [](PirListener *l) -> void {
        l->onPirDetected();
    });
}

void PhysicalSystemImpl::onTm2WakeUp(void) {
    PhysicalSystemImpl::disableInterrupts();
    for_each(buttonListeners.begin(), buttonListeners.end(), [](ButtonListener *l) -> void {
        l->onButtonPress(TM2_BUTTON_CODE);
    });
}

void PhysicalSystemImpl::onTm3WakeUp(void) {
    PhysicalSystemImpl::disableInterrupts();
    for_each(buttonListeners.begin(), buttonListeners.end(), [](ButtonListener *l) -> void {
        l->onButtonPress(TM3_BUTTON_CODE);
    });
}

void PhysicalSystemImpl::disableInterrupts(void) {
    detachInterrupt(digitalPinToInterrupt(PIR_PIN));
    detachInterrupt(digitalPinToInterrupt(TM2_PIN));
    /* disable the interrupts for pin 13, equivalent to PCMSK0 |= 0b00000000; */
    *digitalPinToPCMSK(TM3_PIN) &= ~(1<<digitalPinToPCMSKbit(TM3_PIN));
}


ISR(PCINT0_vect) {
    (PhysicalSystemImpl::onTm3WakeUp)();
}
