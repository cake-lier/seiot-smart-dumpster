/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "CommunicationSystemImpl.h"
#include "MessageParserImpl.h"

#define BT_RX 2
#define BT_TX 3

CommunicationSystemImpl::CommunicationSystemImpl(void)
    : btChannel(new SoftwareSerial(BT_RX, BT_TX)), parser(new MessageParserImpl()) {
    this->btChannel->begin(9600);
}

CommunicationSystemImpl::~CommunicationSystemImpl(void) {
    delete this->btChannel;
    delete this->parser;
}

Message CommunicationSystemImpl::receiveMessage() const {
    // Only single character messages are considered in this system
    return this->btChannel->available() ? this->parser->decodeCharToMessage((char) this->btChannel->read()) : Message::EMPTY;
}

void CommunicationSystemImpl::sendMessage(const Message message) const {
    this->btChannel->print(this->parser->encodeMessageToChar(message));
}