/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "PhysicalSystemImpl.h"
#include "LedImpl.h"
#include "ServoMotorImpl.h"
#include <Arduino.h>

/* pins */
#define LED_A 7
#define LED_B 6
#define LED_C 5
#define SERVO_PIN 9
/* constants */
#define DEGREE_MAX 180
#define DEGREE_MIN 0

PhysicalSystemImpl::PhysicalSystemImpl(void) {
    this->trashLedA = new LedImpl(LED_A);
    this->trashLedB = new LedImpl(LED_B);
    this->trashLedC = new LedImpl(LED_C);
    this->servo = new ServoMotorImpl(SERVO_PIN);
    this->servo->turnOn();
    this->activeLed = NULL;
}

PhysicalSystemImpl::~PhysicalSystemImpl(void) {
    delete this->trashLedA;
    delete this->trashLedB;
    delete this->trashLedC;
    delete this->servo;
}

void PhysicalSystemImpl::turnOnTrashALed(void) {
    this->trashLedA->switchOn();
    this->activeLed = this->trashLedA;
}

void PhysicalSystemImpl::turnOnTrashBLed(void) {
    this->trashLedB->switchOn();
    this->activeLed = this->trashLedB;
}

void PhysicalSystemImpl::turnOnTrashCLed(void) {
    this->trashLedC->switchOn();
    this->activeLed = this->trashLedC;
}

void PhysicalSystemImpl::turnOffActiveTrashLed(void) {
    if (this->activeLed) {
        this->activeLed->switchOff();
        this->activeLed = NULL;
    }
}

void PhysicalSystemImpl::openServo(void) {
    this->servo->moveToDegree(DEGREE_MAX);
}

void PhysicalSystemImpl::closeServo(void) {
    this->servo->moveToDegree(DEGREE_MIN);
}