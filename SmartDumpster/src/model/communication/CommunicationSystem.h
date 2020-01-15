/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __COMM_SYS__
#define __COMM_SYS__

#include "Message.h"

/*
 * The communication system, the class responsible for making the software communicating with the outside. It's required to be
 * capable of sending and receiving messages following a specific format. There is no need for checking if the message queue has
 * messages in a given moment or not, the method for receiving messages will return a special message giving the information that
 * there were no new messages.
 */
class CommunicationSystem { 
    public:
        /*
         * It returns the first message in the received messages queue if there was one, an empty message otherwise.
         */
        virtual Message receiveMessage(void) const = 0;
        /*
         * It sends the given message.
         */
        virtual void sendMessage(const Message message) const = 0;
        /*
         * Default destructor.
         */
        virtual ~CommunicationSystem(void) {};
};

#endif