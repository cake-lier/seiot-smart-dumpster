#ifndef __MESSAGE_PARSER_IMPL__
#define __MESSAGE_PARSER_IMPL__

#include "MessageParser.h"

/*
 * A parser for the messages received through a serial connection.
 */
class MessageParserImpl : public MessageParser {
    public:
        /* 
         * Default constructor.
         */
        MessageParserImpl(void) {}
        /*
         * Default destructor.
         */
        ~MessageParserImpl(void) {}
        /*
         * Parses the string and returns the corresponding Message.
         */
        Message parseStrToMsg(const String stringMessage) const override;
        /*
         * Returns the string corresponding to the Message.
         */
        String parseMsgToStr(const Message message) const override;
};

#endif