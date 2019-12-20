#include <Arduino.h>
#include <ArduinoSTL.h>

#include "SystemContext.h"
#include "src/model/communication/CommunicationSystemImpl.h"
#include "src/model/communication/MessageParserImpl.h"

void setup() {
    Serial.begin(9600); // DEBUG:
    SystemContext::init();
    Serial.println("Setup terminated"); // DEBUG:
}

void loop() {
    Serial.println("run"); // DEBUG:
    SystemContext::getInstance()->run();
}
