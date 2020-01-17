/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "MessageParserImpl.h"

MessageParserImpl::MessageParserImpl(void)
    : charToMessage(new map<char, Message>({
          {'A', Message::START_DEPOSIT_TRASH_A},
          {'B', Message::START_DEPOSIT_TRASH_B},
          {'C', Message::START_DEPOSIT_TRASH_C},
          {'K', Message::KEEP_OPEN},
          {'P', Message::PREMATURE_END_DEPOSIT}
      })), 
      messageToChar(new map<Message, char>({
          {Message::DEPOSIT_HAS_STARTED, 'S'},
          {Message::END_DEPOSIT, 'E'}
      })) {}

MessageParserImpl::~MessageParserImpl(void) {
    delete this->charToMessage;
    delete this->messageToChar;
}

Message MessageParserImpl::decodeCharToMessage(const char charMessage) const {
    return this->charToMessage->find(charMessage) != this->charToMessage->end()
           ? this->charToMessage->find(charMessage)->second
           : Message::EMPTY;
}

char MessageParserImpl::encodeMessageToChar(const Message message) const {
    return this->messageToChar->find(message) != this->messageToChar->end()
           ? this->messageToChar->find(message)->second
           : '\0';
}