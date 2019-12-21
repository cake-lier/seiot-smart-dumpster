#include "StartDepositEventHandler.h"

StartDepositEventHandler::StartDepositEventHandler(const Service &service, const bool &isAvailable, bool &isWeightPolling)
    : AbstractEventHandler(EventType::FORCE_STATE_AVAILABLE), service(service), isAvailable(isAvailable),
      isWeightPolling(isWeightPolling) {}

StartDepositEventHandler::~StartDepositEventHandler(void) {}

void StartDepositEventHandler::execute(void) const {
    if (this->isAvailable) {
        this->isWeightPolling = true;
        //TODO: service
    } else {
        //TODO: service
    }
}