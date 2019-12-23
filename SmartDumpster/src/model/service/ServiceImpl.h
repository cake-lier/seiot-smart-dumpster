/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __SERVICE_IMPL__
#define __SERVICE_IMPL__

#include "Service.h"
#include <LinkedList.h>
#include <ESP8266WebServer.h>

/*
 * 
 */
class ServiceImpl: public Service { 
    public:
        /*
         * 
         */
        ServiceImpl(void);
        /*
         * Default destructor.
         */
        ~ServiceImpl(void);
        /*
         *
         */
        bool isMessageAvailable(void) const;
        /*
         *
         */
        const Message *receiveMessage(void);
        /*
         *
         */
        String sendMessage(const MessageType type, const String resource, const JsonDocument &payload) const;
    private:
        ESP8266WebServer * const server;
        LinkedList<const Message *> * const messageBox;
};

#endif
