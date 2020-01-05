#include <Arduino.h>
#include <ArduinoSTL.h>

#include "SystemContext.h"
#include "src/model/communication/CommunicationSystemImpl.h"
#include "src/model/communication/MessageParserImpl.h"

#include "CommSys.h"

SoftwareSerial *bt = new SoftwareSerial(2,3);// DEBUG:
CommunicationSystemImpl *comm = new CommunicationSystemImpl(bt, new MessageParserImpl()); // DEBUG:

void setup() {
    Serial.begin(9600); // DEBUG:
    bt->begin(9600);
    SystemContext::init(bt);
    Serial.println("Setup terminated"); // DEBUG:
}

// TODO: DEBUG version works. No debug version doesn't
void loop() {
    SystemContext::getInstance()->run();
    // if (bt->available()) { // DEBUG:
    //     Serial.println(bt->read()); // DEBUG:
    // } // DEBUG:
    //Message msg = comm->getMessage();
}
