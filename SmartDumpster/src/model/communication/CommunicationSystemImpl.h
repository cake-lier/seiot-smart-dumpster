/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __COMM_SYS_IMPL__
#define __COMM_SYS_IMPL__

#include "CommunicationSystem.h"
#include "MessageParser.h"
#include <SoftwareSerial.h>

/*
 * The communication system, the class responsible for allowing the software to communicate with the outside. It's required to be
 * capable of sending and receiving messages following a specific format. There is no need for checking if the message queue has
 * messages in a given moment or not, the method for receiving messages will return a special message if
 * there were no new messages.
 */
class CommunicationSystemImpl : public CommunicationSystem { 
    public:
        /*
         * Default constructor.
         */
        CommunicationSystemImpl(void);
        /*
         * Default destructor.
         */
        ~CommunicationSystemImpl(void);
        /*
         * Returns the first Message from the received messages queue, an emtpy Message if the queue is empty.
         */
        Message receiveMessage(void) const override;
        /*
         * Sends the given message.
         */
        void sendMessage(const Message message) const override;
    private:
        SoftwareSerial * const btChannel;
        MessageParser * const parser;
};

#endif