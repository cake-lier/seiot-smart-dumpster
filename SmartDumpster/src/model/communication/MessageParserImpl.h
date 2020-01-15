/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __MESSAGE_PARSER_IMPL__
#define __MESSAGE_PARSER_IMPL__

#include "MessageParser.h"
#include <map>

using namespace std;

/*
 * A parser for the messages received through a serial connection.
 */
class MessageParserImpl : public MessageParser {
    public:
        /* 
         * Default constructor.
         */
        MessageParserImpl(void);
        /*
         * Default destructor.
         */
        ~MessageParserImpl(void);
        /*
         * Parses the string and returns the corresponding Message.
         */
        Message decodeCharToMessage(const char charMessage) const override;
        /*
         * Returns the string corresponding to the Message.
         */
        char encodeMessageToChar(const Message message) const override;
    private:
        const map<char, Message> * const charToMessage;
        const map<Message, char> * const messageToChar;
};

#endif