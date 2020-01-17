/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "EventGeneratorImpl.h"
#include "../../../GlobalConstants.h"
#include <algorithm>
#include <utility>

#define T_DELIVER 60000U / PERIOD // milliseconds

EventGeneratorImpl::EventGeneratorImpl(void) 
    : messageToEvent(new map<Message, Event>({
        {Message::START_DEPOSIT_TRASH_A, Event::START_DEPOSIT_TRASH_A},
        {Message::START_DEPOSIT_TRASH_B, Event::START_DEPOSIT_TRASH_B},
        {Message::START_DEPOSIT_TRASH_C, Event::START_DEPOSIT_TRASH_C},
        {Message::END_DEPOSIT, Event::END_DEPOSIT},
        {Message::KEEP_OPEN, Event::KEEP_OPEN},
        {Message::PREMATURE_END_DEPOSIT, Event::PREMATURE_END_DEPOSIT}
      })),
      intervalToEvent(new map<unsigned int, const vector<Event> *>({
          {T_DELIVER, new const vector<Event>({Event::END_DEPOSIT})}
      })) {}

EventGeneratorImpl::~EventGeneratorImpl(void) {
    delete this->messageToEvent;
    for_each(this->intervalToEvent->begin(),
             this->intervalToEvent->end(),
             [&](const pair<unsigned int, const vector<Event> *> pair) -> void {
        delete pair.second;
    });
    delete this->intervalToEvent;
}

Event EventGeneratorImpl::generateEventFromMessage(const Message message) const {
    return this->messageToEvent->find(message) != this->messageToEvent->end()
           ? this->messageToEvent->find(message)->second
           : Event::EMPTY;
}

vector<Event> *EventGeneratorImpl::generatePeriodicEvent(const unsigned int currentInstant) const {
    auto events = new vector<Event>();
    for_each(this->intervalToEvent->begin(),
             this->intervalToEvent->end(),
             [&](const pair<unsigned int, const vector<Event> *> pair) -> void {
        if (currentInstant >= pair.first) {
            for_each(pair.second->begin(), pair.second->end(), [&](const Event e) -> void {
                events->push_back(e);
            });
        }
    });
    if (events->size() == 0) {
        events->push_back(Event::EMPTY);
    }
    return events;
}