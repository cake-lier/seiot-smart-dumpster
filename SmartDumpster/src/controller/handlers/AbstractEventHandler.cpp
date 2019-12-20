/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "AbstractEventHandler.h"

AbstractEventHandler::AbstractEventHandler(const EventType type) {
    this->type = type;
}

bool AbstractEventHandler::isForEvent(const Event &event) const {
    return event.getType() == this->type;
}
