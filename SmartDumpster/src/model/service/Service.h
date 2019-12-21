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
        virtual const Message *receiveMessage(void) const = 0;
        /*
         *
         */
        virtual void sendMessage(const MessageType type,
                                 const int code,
                                 const DynamicJsonDocument payload) const = 0;
        /*
         * Default destructor.
         */
        virtual ~Service(void) {}
};

#endif
