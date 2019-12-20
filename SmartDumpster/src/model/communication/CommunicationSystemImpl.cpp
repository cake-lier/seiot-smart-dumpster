#include <SoftwareSerial.h>
#include "CommunicationSystemImpl.h"

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
        String str = String((char) this->btChannel->read());
        return this->parser->parseStrToMsg(str);
    } else {
        return Message::EMPTY;
    }
}

void CommunicationSystemImpl::sendMessage(const Message message) {
    this->btChannel->println(this->parser->parseMsgToStr(message));
}