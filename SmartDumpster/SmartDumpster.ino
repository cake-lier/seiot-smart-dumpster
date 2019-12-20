#include <Arduino.h>
#include <ArduinoSTL.h>

#include "SystemContext.h"

void setup() {
    Serial.begin(9600); // DEBUG:
    Serial.println("Setup terminated"); // DEBUG:
}

void loop() {
    Serial.println("run"); // DEBUG:
    SystemContext::getInstance()->run();
}
