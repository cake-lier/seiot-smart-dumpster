/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __MESSAGE__
#define __MESSAGE__

#include "MessageType.h"
#include <Arduino.h>
#include <ArduinoJson.h>
/*
 * 
 */
class Message { 
    public:
        /*
         *
         */
        virtual MessageType getType(void) const = 0;
        /*
         *
         */
        virtual String getResource(void) const = 0;
        /*
         *
         */
        virtual const JsonDocument &getPayload(void) const = 0;
        /*
         * Default destructor.
         */
        virtual ~Message(void) {}
};

#endif
