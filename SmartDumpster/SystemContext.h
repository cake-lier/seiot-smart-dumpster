/* Authors: Matteo Castellucci, Giorgia Rondinini */
#ifndef __SYSTEM_CONTEXT__
#define __SYSTEM_CONTEXT__

#include "src/controller/Controller.h"
#include <SoftwareSerial.h>

/*
 * The class encompassing the entire system the Arduino should run. It's made of physical components all grouped
 * together, a scheduler so as to execute the logic based on the the physical components and a console to which send
 * and from which receive all information needed.
 */
class SystemContext {
    public:
        /*
         * It returns the only instance of this class. Being the system as a whole, there couldn't be two systems on the
         * same Arduino.
         */
        static SystemContext *getInstance(void);
        /*
         * Static method to be called before starting to run the system. It initializes it.
         */
        static void init(SoftwareSerial *btc);
        /*
         * It executes the logic of the system one step at a time. It should be put into an endless loop.
         */
        void run(void);
    private:
        /*
         * Default constructor, the singleton pattern requires it to be private. It will be the job of the init() method
         * to create the only instance of this class.
         */
        SystemContext(SoftwareSerial *btc);
        /*
         * Default destructor. The system should be destroyed when the Arduino is shut down, but because it should
         * endlessly run, there is no need to make it public.
         */
        ~SystemContext(void);
        static SystemContext *SINGLETON;
        Controller *controller;
};

#endif
