/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __EVENT__
#define __EVENT__

/*
 * The enum collecting all events that can happen into this system.
 */
enum class Event {
    /*
     * The event corresponding to the beginning of a deposit of trash of type A.
     */
    START_DEPOSIT_TRASH_A,
    /*
     * The event corresponding to the beginning of a deposit of trash of type B.
     */
    START_DEPOSIT_TRASH_B,
    /*
     * The event corresponding to the beginning of a deposit of trash of type C.
     */
    START_DEPOSIT_TRASH_C,
    /*
     * The event corresponding to the end of a deposit of trash of any type.
     */
    END_DEPOSIT,
    /*
     * The event corresponding to a request of resetting the time for which the trashcan door is being kept open.
     */
    KEEP_OPEN,
    /*
     * The event corresponding to the termination of a deposit before time.
     */
    PREMATURE_END_DEPOSIT,
    /*
     * The empty event, which as part of its definition has no meaning and triggers no handlers.
     */
    EMPTY
};

#endif