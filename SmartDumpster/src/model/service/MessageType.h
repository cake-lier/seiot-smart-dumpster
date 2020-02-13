/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __MESSAGE_TYPE__
#define __MESSAGE_TYPE__

/*
 * An enum representing the possible types of messages to send to or receive from the Service.
 */
enum class MessageType {
    /*
     * This type is for a message that needs to read the value of a resource from this system.
     */
    READ,
    /*
     * This type is for a message that needs to apply changes to a resource in this system.
     */
    MODIFY,
    /*
     * This type is for a message that is a response to an already received message.
     */
    RESPONSE
};

#endif
