/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __MESSAGE_PARSER__
#define __MESSAGE_PARSER__

#include "Message.h"

/*
 * A parser class which can encode messages into their char form and can decode them from their char form.
 */
class MessageParser {
    public:
        /*
         * It parses the passed char and decodes it into the corresponding message.
         */
        virtual Message decodeCharToMessage(const char charMessage) const = 0;
        /*
         * It encodes the passed message into the corrisponding char.
         */
        virtual char encodeMessageToChar(const Message message) const = 0;
        /*
         * Default destructor.
         */
        virtual ~MessageParser(void) {};
};

#endif