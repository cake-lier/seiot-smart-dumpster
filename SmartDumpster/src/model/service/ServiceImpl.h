/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __SERVICE_IMPL__
#define __SERVICE_IMPL__

#include "Service.h"
#include <LinkedList.h>
#include <ESP8266WebServer.h>

/*
 * A class representing the Service part of the SmartDumpster, with which the ESP8266 
 * can communicate, using HTTP as the communication protocol.
 */
class ServiceImpl: public Service { 
    public:
        /*
         * The default constructor. 
         */
        ServiceImpl(void);
        /*
         * Default destructor.
         */
        ~ServiceImpl(void);
        /*
         * Returns whether a message from the Service has arrived and is queued, waiting to be read.
         */
        bool isMessageAvailable(void) const;
        /*
         * Reads a message from the queue of messages received from the Service.
         */
        const Message *receiveMessage(void);
        /*
         * Sends a message to the Service.
         */
        String sendMessage(const MessageType type, const String resource, const JsonDocument &payload) const;
    private:
        ESP8266WebServer * const server;
        LinkedList<const Message *> * const messageBox;
};

#endif
