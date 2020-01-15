#include "SmartDumpster.h"

void setup() {
    SystemContext::init();
}

void loop() {
    SystemContext::getInstance()->run();
}
