/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __MESSAGE_TYPE__
#define __MESSAGE_TYPE__

/*
 * An enum representing the possible types of messages to send to or receive from the Service.
 */
enum class MessageType { 
    READ,
    MODIFY,
    RESPONSE
};

#endif
