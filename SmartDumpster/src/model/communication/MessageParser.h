#ifndef __MESSAGE_PARSER__
#define __MESSAGE_PARSER__

#include "Message.h"
#include <ArduinoSTL.h>
#include <Arduino.h>

/*
 * A parser for the messages received through a serial connection.
 */
class MessageParser {
    public:
        /*
         * Parses the string and returns the corresponding Message.
         */
        virtual Message parseStrToMsg(String) const = 0;
        /*
         * Returns the string corresponding to the Message.
         */
        virtual String parseMsgToStr(Message) const = 0;
};

#endif