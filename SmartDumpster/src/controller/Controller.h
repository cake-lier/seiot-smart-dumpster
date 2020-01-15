/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __CONTROLLER__
#define __CONTROLLER__

/*
 * The root class of the controller component of this software, it has the job of coordinating the use of all model elements so
 * as to put into execution its logic.
 */
class Controller {
    public:
        /*
         * It runs one iteration of the loop that executes the application.
         */
        virtual void run(void) = 0;
        /*
         * Default destructor.
         */
        virtual ~Controller(void) {};
};

#endif