/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __EVENT_TYPE__
#define __EVENT_TYPE__

/*
 * An enum representing the types of events that can happen in the system.
 */
enum class EventType {
    /*
     * The type of event representing the beginning of a deposit.
     */
    BEGIN_DEPOSIT,
    /*
     * The type of event representing the ending of a deposit.
     */
    END_DEPOSIT,
    /*
     * The type of event representing the request for the current state of this system.
     */
    GET_STATE,
    /*
     * The type of event representing the forcing of this system to the "available" state.
     */
    FORCE_STATE_AVAILABLE,
    /*
     * The type of event representing the forcing of this system to the "unavailable" state.
     */
    FORCE_STATE_UNAVAILABLE
};

#endif
