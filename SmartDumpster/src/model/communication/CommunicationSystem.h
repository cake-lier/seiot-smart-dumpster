#ifndef __COMM_SYS__
#define __COMM_SYS__

#include "Message.h"

class CommunicationSystem { 
    public:
        /*
         * Returns true if there is a message available.
         */
        virtual bool isAvailable(void) = 0;
        /*
         * Returns the first message in the received messages queue.
         */
        virtual Message getMessage(void) = 0;
        /*
         * Sends the given message.
         */
        virtual void sendMessage(Message) = 0;
};

#endif