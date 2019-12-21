#include "GetStateEventHandler.h"

GetStateEventHandler::GetStateEventHandler(const Service &service, const bool &isAvailable)
    : AbstractEventHandler(EventType::FORCE_STATE_UNAVAILABLE), service(service), isAvailable(isAvailable) {}

GetStateEventHandler::~GetStateEventHandler(void) {}

void GetStateEventHandler::execute(void) const {
    //TODO: Service
}