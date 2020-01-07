#include <Arduino.h>
#include <ArduinoSTL.h>

#include "SystemContext.h"
#include "src/model/communication/CommunicationSystemImpl.h"
#include "src/model/communication/MessageParserImpl.h"

SoftwareSerial *bt = new SoftwareSerial(2,3);

void setup() {
    bt->begin(9600);
    SystemContext::init(bt);
}

void loop() {
    SystemContext::getInstance()->run();
}
