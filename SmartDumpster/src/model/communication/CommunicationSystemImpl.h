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
        CommunicationSystemImpl(const int txPin, const int rxPin, MessageParser *parser);
        /*
         * Default destructor.
         */
        ~CommunicationSystemImpl(void);
        /*
         * Returns true if there is a message available.
         */
        bool isAvailable(void) override;
        /*
         * Returns the first message in the received messages queue.
         */
        Message getMessage(void) override;
        /*
         * Sends the given message.
         */
        void sendMessage(Message) override;
        void voided() override; // DEBUG:
    private:
        SoftwareSerial *btChannel;
        MessageParser *parser;
};

#endif