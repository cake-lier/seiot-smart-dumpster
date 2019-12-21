#include "EndDepositEventHandler.h"
#include "../../model/physics/PhysicsConstants.h"

EndDepositEventHandler::EndDepositEventHandler(const Service &service,
                                               bool &isAvailable,
                                               bool &isWeightPolling,
                                               const int &currentWeight)
    : AbstractEventHandler(EventType::FORCE_STATE_AVAILABLE), service(service), currentWeight(currentWeight), 
      isAvailable(isAvailable), isWeightPolling(isWeightPolling) {}

EndDepositEventHandler::~EndDepositEventHandler(void) {}

void EndDepositEventHandler::execute(void) const {
    this->isWeightPolling = false;
    if (this->currentWeight >= MAX_WEIGHT) {
        this->isAvailable = false;
    }
    //TODO: Service
}