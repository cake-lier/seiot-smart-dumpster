/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "EventImpl.h"

EventImpl::EventImpl(const EventType type) : type(type) {}

EventImpl::~EventImpl(void) {}

EventType EventImpl::getType(void) const {
    return this->type;
}