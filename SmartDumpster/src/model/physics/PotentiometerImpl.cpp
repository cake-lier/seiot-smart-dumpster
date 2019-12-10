/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "PotentiometerImpl.h"
#include <Arduino.h>

#define ANALOG_MIN 0
#define ANALOG_MAX 1023

PotentiometerImpl::PotentiometerImpl(const int pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

PotentiometerImpl::~PotentiometerImpl(void) {}

int PotentiometerImpl::readMappedValue(const int min, const int max) const {
    return map(analogRead(this->pin), ANALOG_MIN, ANALOG_MAX, min, max);
}
