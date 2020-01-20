/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __EVENT_SCHEDULER__
#define __EVENT_SCHEDULER__

/*
 * A class used to execute a step of the system life. 
 */
class EventScheduler { 
    public:
        /*
         * Executes a step. 
         */
        virtual void step(void) = 0;
        /*
         * Default destructor.
         */
        virtual ~EventScheduler(void) {}
};

#endif
