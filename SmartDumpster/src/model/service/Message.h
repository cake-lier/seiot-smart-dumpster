/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __MESSAGE__
#define __MESSAGE__

#include "MessageType.h"
#include <Arduino.h>
#include <ArduinoJson.h>
/*
 * A message from the Edge to the Service, or viceversa. 
 */
class Message { 
    public:
        /*
         * Returns the type of this message.
         */
        virtual MessageType getType(void) const = 0;
        /*
         Returns where this message should be sent, or from where it has been sent. 
         */
        virtual String getResource(void) const = 0;
        /*
         * Returns the content of this message as a JsonDocument.
         */
        virtual const JsonDocument &getPayload(void) const = 0;
        /*
         * Default destructor.
         */
        virtual ~Message(void) {}
};

#endif
