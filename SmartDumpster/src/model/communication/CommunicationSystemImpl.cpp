#include <SoftwareSerial.h>
#include "CommunicationSystemImpl.h"

CommunicationSystemImpl::CommunicationSystemImpl(SoftwareSerial *btc, MessageParser *parser) {
    this->btChannel = btc;
    this->parser = parser;
}

CommunicationSystemImpl::~CommunicationSystemImpl(void) {
    delete this->btChannel;
    delete this->parser;
}

Message CommunicationSystemImpl::getMessage() {
    // only single character messages are considered in this system
    if (this->btChannel->available()) {
        char rc = (char) this->btChannel->read();
        Serial.println(rc);
        String str = String(rc);
        return this->parser->parseStrToMsg(str);
    } else {
        return Message::EMPTY;
    }
}

void CommunicationSystemImpl::sendMessage(const Message message) {
    this->btChannel->println(this->parser->parseMsgToStr(message));
}