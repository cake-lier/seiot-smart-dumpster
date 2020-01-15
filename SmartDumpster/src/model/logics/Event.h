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
     * The event corresponding to the ending of a deposit of trash of any type.
     */
    END_DEPOSIT,
    /*
     * The event corresponding to a request of resetting the time for which the trashcan door is being keeping open.
     */
    KEEP_OPEN,
    /*
     * The empty event, which as part of its definition has no meaning and triggers no handlers.
     */
    EMPTY
};

#endif