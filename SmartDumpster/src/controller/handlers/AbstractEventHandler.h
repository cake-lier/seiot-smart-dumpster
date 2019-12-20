/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __ABSTRACT_EVENT_HANDLER__
#define __ABSTRACT_EVENT_HANDLER__

#include "EventHandler.h"
#include "../EventType.h"

/*
 * 
 */
class AbstractEventHandler: public EventHandler { 
    public:
        /*
         * 
         */
        bool isForEvent(const Event &event) const override;
        /*
         * 
         */
        virtual void execute(void) const = 0;
        /*
         * Default destructor.
         */
        virtual ~AbstractEventHandler(void) {}
    protected:
        /*
         *
         */
        AbstractEventHandler(const EventType type);
    private:
        EventType type;
};

#endif
