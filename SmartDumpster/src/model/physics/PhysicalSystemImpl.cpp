/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "PhysicalSystemImpl.h"
#include "LedImpl.h"
#include "PotentiometerImpl.h"
#include <Arduino.h>

/* pins */
#define POT_PIN A0
#define LA_PIN D3
#define LNA_PIN D1
/* constants */
#define WEIGHT_MIN 1
#define WEIGHT_MAX 100

PhysicalSystemImpl::PhysicalSystemImpl(void) {
    this->availableLed = new LedImpl(LA_PIN);
    this->notAvailableLed = new LedImpl(LNA_PIN);
    this->potentiometer = new PotentiometerImpl(POT_PIN);
}

PhysicalSystemImpl::~PhysicalSystemImpl(void) {
    delete this->availableLed;
    delete this->notAvailableLed;
    delete this->potentiometer;
}

void PhysicalSystemImpl::turnOnAvailableLed(void) {
    this->availableLed->switchOn();
}

void PhysicalSystemImpl::turnOffAvailableLed(void) {
    this->availableLed->switchOff();
}

void PhysicalSystemImpl::turnOnNotAvailableLed(void) {
    this->notAvailableLed->switchOn();
}

void PhysicalSystemImpl::turnOffNotAvailableLed(void) {
    this->notAvailableLed->switchOff();
}

int PhysicalSystemImpl::getWeight(void) const {
    return this->potentiometer->readMappedValue(WEIGHT_MIN, WEIGHT_MAX);
}

