/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __EVENT_GENERATOR_IMPL__
#define __EVENT_GENERATOR_IMPL__

#include "EventGenerator.h"
#include <map>

/*
 * A source of events which can generate them from an incoming message from the communication system or periodicly knowing the
 * time interval between the initial instant and the current instant given in periods of the synchronous finite state machine upon
 * which this software is built.
 */
class EventGeneratorImpl : public EventGenerator {
    public:
        /*
         * Default constructor.
         */
        EventGeneratorImpl(void);
        /*
         * Default destructor.
         */
        ~EventGeneratorImpl(void);
        /*
         * It generates a new event from an incoming message from the communication system.
         */
        Event generateEventFromMessage(const Message message) const override;
        /*
         * It generates new events if the associated period has passed.
         * The period is given in periods of the synchronous finite state
         * machine upon which this software is built.
         */
        vector<Event> *generatePeriodicEvents(const unsigned int currentInstant) const override;
    private:
        const map<Message, Event> * const messageToEvent;
        const map<unsigned int, const vector<Event> *> * const intervalToEvent;
};

#endif