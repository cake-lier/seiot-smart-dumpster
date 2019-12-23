#include "EndDepositEventHandler.h"
#include "../../model/physics/PhysicsConstants.h"

EndDepositEventHandler::EndDepositEventHandler(const PhysicalSystem &physics,
                                               const Service &service,
                                               bool &isAvailable,
                                               bool &isWeightPolling,
                                               int &currentWeight)
    : AbstractEventHandler(EventType::END_DEPOSIT), physics(physics), service(service), currentWeight(currentWeight), 
      isAvailable(isAvailable), isWeightPolling(isWeightPolling) {}

EndDepositEventHandler::~EndDepositEventHandler(void) {}

void EndDepositEventHandler::execute(void) const {
    this->isWeightPolling = false;
    int weightWaiting = this->physics.getWeight();
    if (weightWaiting + this->currentWeight >= MAX_WEIGHT) {
        this->isAvailable = false;
    }
    DynamicJsonDocument messageBody(47);
    messageBody["success"] = true;
    messageBody["weight"] = weightWaiting;
    this->service.sendMessage(MessageType::RESPONSE, "/deposit", messageBody);
    this->currentWeight += weightWaiting;
}