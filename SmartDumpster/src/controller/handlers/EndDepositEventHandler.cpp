#include "EndDepositEventHandler.h"
#include "../../model/physics/PhysicsConstants.h"

EndDepositEventHandler::EndDepositEventHandler(PhysicalSystem &physics,
                                               const Service &service,
                                               bool &isAvailable,
                                               bool &isWeightPolling,
                                               int &currentWeight)
    : AbstractEventHandler(EventType::END_DEPOSIT), physics(physics), service(service), currentWeight(currentWeight), 
      isAvailable(isAvailable), isWeightPolling(isWeightPolling) {}

EndDepositEventHandler::~EndDepositEventHandler(void) {}

void EndDepositEventHandler::execute(void) const {
    DynamicJsonDocument messageBody(47);
    if (this->isWeightPolling) {
        this->isWeightPolling = false;
        int weightWaiting = this->physics.getWeight();
        if (weightWaiting + this->currentWeight >= MAX_WEIGHT) {
            this->isAvailable = false;
            this->physics.turnOffAvailableLed();
            this->physics.turnOnNotAvailableLed();
        }
        this->currentWeight += weightWaiting;
        messageBody["success"] = true;
        messageBody["weight"] = weightWaiting;
    } else {
        messageBody["success"] = false;
    }
    this->service.sendMessage(MessageType::RESPONSE, "/deposit", messageBody);
}