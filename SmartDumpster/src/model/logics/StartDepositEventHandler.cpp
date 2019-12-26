#include "StartDepositEventHandler.h"

StartDepositEventHandler::StartDepositEventHandler(const Service &service, const bool &isAvailable, bool &isWeightPolling)
    : AbstractEventHandler(EventType::BEGIN_DEPOSIT), service(service), isAvailable(isAvailable),
      isWeightPolling(isWeightPolling) {}

StartDepositEventHandler::~StartDepositEventHandler(void) {}

void StartDepositEventHandler::execute(void) const {
    DynamicJsonDocument messageBody(24);
    if (this->isAvailable && !this->isWeightPolling) {
        this->isWeightPolling = true;
        messageBody["success"] = true;
        messageBody["deposit"] = "begin";
    } else {
        messageBody["success"] = false;
    }
    this->service.sendMessage(MessageType::RESPONSE, "/deposit", messageBody);
}