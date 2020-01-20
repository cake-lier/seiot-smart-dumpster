/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __MESSAGE_IMPL__
#define __MESSAGE_IMPL__

#include "Message.h"

/*
 * 
 */
class MessageImpl: public Message { 
    public:
        /*
         * Constructor. Requires the type of the message being built, the route where the message
         * will be sent (or the route from which it has been received) and the content of the message
         * as a JsonDocument.
         */
        MessageImpl(const MessageType type,
                    const String resource,
                    const JsonDocument * const payload);
        /*
         * Default destructor.
         */
        ~MessageImpl(void);
        /*
         * Returns the type of this message.
         */
        MessageType getType(void) const override;
        /*
         * Returns where this message should be sent, or from where it has been sent. 
         * It's an HTTP route managed by the Service.
         */
        String getResource(void) const override;
        /*
         * Returns the content of this message as a JsonDocument.
         */
        const JsonDocument &getPayload(void) const override;
    private:
        const MessageType type;
        const String resource;
        const JsonDocument * const payload;
};

#endif
