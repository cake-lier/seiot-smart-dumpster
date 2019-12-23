#include "MessageImpl.h"

MessageImpl::MessageImpl(const MessageType type,
                         const String resource,
                         const JsonDocument * const payload)
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

const JsonDocument &MessageImpl::getPayload(void) const {
    return *this->payload;
}
