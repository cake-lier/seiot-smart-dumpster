/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __SERVICE__
#define __SERVICE__

#include "Message.h"
#include "MessageType.h"
#include <ArduinoJson.h>

/*
 * 
 */
class Service { 
    public:
        /*
         *
         */
        virtual bool isMessageAvailable(void) const = 0;
        /*
         *
         */
        virtual const Message *receiveMessage(void) = 0;
        /*
         *
         */
        virtual String sendMessage(const MessageType type, const String resource, const JsonDocument &payload) const = 0;
        /*
         * Default destructor.
         */
        virtual ~Service(void) {}
};

#endif
