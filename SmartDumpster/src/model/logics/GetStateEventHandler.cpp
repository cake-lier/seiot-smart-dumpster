#include "GetStateEventHandler.h"

GetStateEventHandler::GetStateEventHandler(const Service &service, const bool &isAvailable, const int &currentWeight)
    : AbstractEventHandler(EventType::GET_STATE), service(service), isAvailable(isAvailable), currentWeight(currentWeight) {}

GetStateEventHandler::~GetStateEventHandler(void) {}

void GetStateEventHandler::execute(void) const {
    DynamicJsonDocument messageBody(50);
    messageBody["available"] = this->isAvailable;
    messageBody["weight"] = this->currentWeight;
    messageBody["success"] = true;
    this->service.sendMessage(MessageType::RESPONSE, "/state", messageBody);
}