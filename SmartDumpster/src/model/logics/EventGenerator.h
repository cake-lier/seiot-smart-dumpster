/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __EVENT_GENERATOR__
#define __EVENT_GENERATOR__

#include "../communication/Message.h"
#include "Event.h"
#include <vector>

using namespace std;

/*
 * A source of events which can generate them from an incoming message from the communication system or periodicly knowing the
 * time interval between the initial instant and the current instant given in periods of the synchronous finite state machine upon
 * which this software is built.
 */
class EventGenerator {
    public:
        /*
         * It generates a new event from an incoming message from the communication system.
         */
        virtual Event generateEventFromMessage(const Message message) const = 0;
        /*
         * It generates new events if the associated period has passed.
         * The period is given in periods of the synchronous finite state
         * machine upon which this software is built.
         */
        virtual vector<Event> *generatePeriodicEvents(const unsigned int currentInstant) const = 0; // TODO: change name
        /*
         * Default destructor.
         */
        virtual ~EventGenerator(void) {};
};

#endif