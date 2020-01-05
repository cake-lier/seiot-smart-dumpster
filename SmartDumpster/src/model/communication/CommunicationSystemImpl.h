#ifndef __COMM_SYS_IMPL__
#define __COMM_SYS_IMPL__

#include "CommunicationSystem.h"
#include "MessageParser.h"
#include <SoftwareSerial.h>

class CommunicationSystemImpl : public CommunicationSystem { 
    public:
        /*
         * Default constructor.
         */
        CommunicationSystemImpl(SoftwareSerial *channel, MessageParser *parser);
        /*
         * Default destructor.
         */
        ~CommunicationSystemImpl(void);
        /*
         * Returns the received messages queue.
         */
        Message getMessage(void) override;
        /*
         * Sends the given message.
         */
        void sendMessage(Message) override;
    private:
        SoftwareSerial *btChannel;
        MessageParser *parser;
};

#endif