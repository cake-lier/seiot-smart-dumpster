/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "ServoMotorImpl.h"
#include <cmath>

#define MIN_PULSE 544.0F
#define MAX_PULSE 2400.0F
#define MAX_DEGREE 180.0F
#define MIN_DEGREE 0.0F
#define PAUSE 10000   // microseconds

ServoMotorImpl::ServoMotorImpl(const int pin) {
    this->pin = pin;
    this->motor = new ServoTimer2();
    this->currentDegree = -1;
}

ServoMotorImpl::~ServoMotorImpl(void) {
    this->motor->detach();
    delete this->motor;
}

void ServoMotorImpl::turnOn() {
    this->motor->attach(this->pin);    
}

void ServoMotorImpl::turnOff() {
    this->motor->detach();    
}

void ServoMotorImpl::moveToDegree(const float degrees) {
    this->currentDegree = degrees > MAX_DEGREE ? MAX_DEGREE : (degrees < MIN_DEGREE ? MIN_DEGREE : degrees);
    this->motor->write(round(MIN_PULSE + this->currentDegree * (MAX_PULSE - MIN_PULSE) / MAX_DEGREE));
    delayMicroseconds(PAUSE);
}

int ServoMotorImpl::getCurrentDegree(void) const {
    return this->currentDegree;
}
