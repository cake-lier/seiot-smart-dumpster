#include "SmartDumpster.h"

void setup() {
    SystemContext::init();
    context = SystemContext::getInstance();
}

void loop() {
    context->run();
}
