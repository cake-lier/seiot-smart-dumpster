/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __EVENT_TYPE__
#define __EVENT_TYPE__

/*
 * An enum representing the types of events that can happen in the system.
 */
enum class EventType {
    BEGIN_DEPOSIT,
    END_DEPOSIT,
    GET_STATE,
    FORCE_STATE_AVAILABLE,
    FORCE_STATE_UNAVAILABLE
};

#endif
