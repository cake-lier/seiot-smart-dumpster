#include "MessageImpl.h"

MessageImpl::MessageImpl(const MessageType type,
                         const String resource,
                         DynamicJsonDocument * const payload)
    : type(type), resource(resource), payload(payload) {}

MessageImpl::~MessageImpl(void) {
    delete this->payload;
}

MessageType MessageImpl::getType(void) const {
    return this->type;
}

String MessageImpl::getResource(void) const {
    return this->resource;
}

DynamicJsonDocument &MessageImpl::getPayload(void) const {
    return *this->payload;
}
