/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __EVENT_SCHEDULER__
#define __EVENT_SCHEDULER__

/*
 * 
 */
class EventScheduler { 
    public:
        /*
         * 
         */
        virtual void step(void) = 0;
        /*
         * Default destructor.
         */
        virtual ~EventScheduler(void) {}
};

#endif
