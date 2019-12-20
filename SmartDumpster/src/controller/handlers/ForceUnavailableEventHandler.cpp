#include "ForceUnavailableEventHandler.h"
#include "../EventType.h"

ForceUnavailableEventHandler::ForceUnavailableEventHandler(PhysicalSystem &physics, const Service &service, bool &isAvailable)
    : AbstractEventHandler(EventType::FORCE_STATE_UNAVAILABLE), physics(physics), service(service), isAvailable(isAvailable) {}

ForceUnavailableEventHandler::~ForceUnavailableEventHandler(void) {}

void ForceUnavailableEventHandler::execute(void) const {
    this->physics.turnOffAvailableLed();
    this->isAvailable = false;
    this->physics.turnOnNotAvailableLed();
    //TODO: Service
}