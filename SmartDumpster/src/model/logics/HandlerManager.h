#ifndef __HANDLER_MANAGER__
#define __HANDLER_MANAGER__

#include "Event.h"

class HandlerManager {
    public:
        virtual void runEventHandler(Event) = 0;;
};

#endif