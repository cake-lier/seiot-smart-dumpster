/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __SERVICE__
#define __SERVICE__

#include "Message.h"
#include "MessageType.h"
#include <ArduinoJson.h>

/*
 * A class representing the Service part of the SmartDumpster, with which the ESP8266 
 * can communicate.
 */
class Service { 
    public:
        /*
         * Returns whether a message from the Service has arrived and is queued, waiting to be read.
         */
        virtual bool isMessageAvailable(void) const = 0;
        /*
         * Reads a message from the queue of messages received from the Service.
         */
        virtual const Message *receiveMessage(void) = 0;
        /*
         * Sends a message to the Service.
         */
        virtual String sendMessage(const MessageType type, const String resource, const JsonDocument &payload) const = 0;
        /*
         * Default destructor.
         */
        virtual ~Service(void) {}
};

#endif
