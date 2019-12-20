#include "SmartDumpster.h"

void setup() {
    context = SystemContext::getInstance();
}

void loop() {
    context->run();
}
