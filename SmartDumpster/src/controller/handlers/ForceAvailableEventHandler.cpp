#include "ForceAvailableEventHandler.h"

ForceAvailableEventHandler::ForceAvailableEventHandler(PhysicalSystem &physics, const Service &service, bool &isAvailable)
    : AbstractEventHandler(EventType::FORCE_STATE_AVAILABLE), physics(physics), service(service), isAvailable(isAvailable) {}

ForceAvailableEventHandler::~ForceAvailableEventHandler(void) {}

void ForceAvailableEventHandler::execute(void) const {
    this->physics.turnOffNotAvailableLed();
    this->isAvailable = true;
    this->physics.turnOnAvailableLed();
    //TODO: Service
}