#include "ForceAvailableEventHandler.h"

ForceAvailableEventHandler::ForceAvailableEventHandler(PhysicalSystem &physics,
                                                       const Service &service,
                                                       bool &isAvailable,
                                                       int &currentWeight)
    : AbstractEventHandler(EventType::FORCE_STATE_AVAILABLE), physics(physics), service(service), isAvailable(isAvailable),
      currentWeight(currentWeight) {}

ForceAvailableEventHandler::~ForceAvailableEventHandler(void) {}

void ForceAvailableEventHandler::execute(void) const {
    this->physics.turnOffNotAvailableLed();
    this->isAvailable = true;
    this->currentWeight = 0;
    this->physics.turnOnAvailableLed();
    DynamicJsonDocument messageBody(24);
    messageBody["success"] = true;
    messageBody["available"] = this->isAvailable;
    this->service.sendMessage(MessageType::RESPONSE, "/state", messageBody);
}