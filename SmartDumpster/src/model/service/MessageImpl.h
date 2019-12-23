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
         * 
         */
        MessageImpl(const MessageType type,
                    const String resource,
                    const JsonDocument * const payload);
        /*
         * Default destructor.
         */
        ~MessageImpl(void);
        /*
         *
         */
        MessageType getType(void) const override;
        /*
         *
         */
        String getResource(void) const override;
        /*
         *
         */
        const JsonDocument &getPayload(void) const override;
    private:
        const MessageType type;
        const String resource;
        const JsonDocument * const payload;
};

#endif
