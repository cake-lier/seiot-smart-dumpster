/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "LedImpl.h"
#include <Arduino.h>

LedImpl::LedImpl(const int pin) {
    this->pin = pin;
    pinMode(this->pin, OUTPUT);
}

LedImpl::~LedImpl(void) {}

void LedImpl::switchOn(void) {
    digitalWrite(this->pin, HIGH);
    this->on = true;
}

void LedImpl::switchOff(void ) {
    digitalWrite(this->pin, LOW);
    this->on = false;
}

bool LedImpl::isOn(void) const {
    return this->on;
}
