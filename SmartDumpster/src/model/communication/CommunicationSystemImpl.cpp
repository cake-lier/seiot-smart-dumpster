#include "CommunicationSystemImpl.h"
#include <SoftwareSerial.h>

CommunicationSystemImpl::CommunicationSystemImpl(const int txPin, const int rxPin, MessageParser *parser) {
    this->btChannel = new SoftwareSerial(txPin, rxPin);
    this->parser = parser;
}

CommunicationSystemImpl::~CommunicationSystemImpl(void) {
    delete this->btChannel;
}

bool CommunicationSystemImpl::isAvailable() {
    return this->btChannel->available();
}

Message CommunicationSystemImpl::getMessage() {
    // only single character messages are considered in this system
    if (this->isAvailable()) {
        return this->parser->parseStrToMsg(String((char) this->btChannel->read()));
    } else {
        return Message::EMPTY;
    }
}

void CommunicationSystemImpl::sendMessage(const Message message) {
    this->btChannel->println(this->parser->parseMsgToStr(message));
}