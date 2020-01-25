/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __MESSAGE__
#define __MESSAGE__

/*
 * This enum represents the various type of messages that this software can understand, and so receive and send.
 */
enum class Message {
    /*
     * This message indicates the beginning of a deposit of trash of type A.
     */
    START_DEPOSIT_TRASH_A,
    /*
     * This message indicates the beginning of a deposit of trash of type B.
     */
    START_DEPOSIT_TRASH_B,
    /*
     * This message indicates the beginning of a deposit of trash of type C.
     */
    START_DEPOSIT_TRASH_C,
    /*
     * This message indicates that the deposit has successfully started.
     */
    DEPOSIT_HAS_STARTED,
    /*
     * This message indicates a request for time extension during the deposit of trash.
     */
    KEEP_OPEN,
    /*
     * This message indicates the end of a deposit.
     */
    END_DEPOSIT,
    /*
     * This message indicates the need of end a deposit before time.
     */
    PREMATURE_END_DEPOSIT,
    /*
     * This message represents the empty message, which has no meaning.
     */
    EMPTY
};

#endif