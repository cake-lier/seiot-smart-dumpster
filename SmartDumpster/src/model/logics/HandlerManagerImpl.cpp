/* Authors: Matteo Castellucci, Giorgia Rondinini */
#include "HandlerManagerImpl.h"
#include "EventHandlerImpl.h"

HandlerManagerImpl::HandlerManagerImpl(PhysicalSystem &system, const CommunicationSystem &commSystem, unsigned int &openCount)
    : physicalSystem(system), commSystem(commSystem), openCount(openCount), handlers(new vector<const EventHandler *>()) {
    auto resetCounter = [&]() -> void {
        this->openCount = 0;
    };
    this->addEventHandler(new EventHandlerImpl<decltype(resetCounter)>(Event::KEEP_OPEN, resetCounter));
    auto startDeposit = [&, resetCounter]() -> void {
        resetCounter();
        this->physicalSystem.openServo();
        this->commSystem.sendMessage(Message::DEPOSIT_HAS_STARTED);
    };
    auto startDepositTrashA = [&, startDeposit]() -> void {
        this->physicalSystem.turnOnTrashALed();
        startDeposit();
    };
    this->addEventHandler(new EventHandlerImpl<decltype(startDepositTrashA)>(Event::START_DEPOSIT_TRASH_A, startDepositTrashA));
    auto startDepositTrashB = [&, startDeposit]() -> void {
        this->physicalSystem.turnOnTrashBLed();
        startDeposit();
    };
    this->addEventHandler(new EventHandlerImpl<decltype(startDepositTrashB)>(Event::START_DEPOSIT_TRASH_B, startDepositTrashB));
    auto startDepositTrashC = [&, startDeposit]() -> void {
        this->physicalSystem.turnOnTrashCLed();
        startDeposit();
    };
    this->addEventHandler(new EventHandlerImpl<decltype(startDepositTrashC)>(Event::START_DEPOSIT_TRASH_C, startDepositTrashC));
    auto prematureEnd = [&, resetCounter]() -> void {
        resetCounter();
        this->physicalSystem.closeServo();
        this->physicalSystem.turnOffActiveTrashLed();
    };
    this->addEventHandler(new EventHandlerImpl<decltype(prematureEnd)>(Event::PREMATURE_END_DEPOSIT, prematureEnd));
    auto endDeposit = [&, prematureEnd]() -> void {
        prematureEnd();
        this->commSystem.sendMessage(Message::END_DEPOSIT);
    };
    this->addEventHandler(new EventHandlerImpl<decltype(endDeposit)>(Event::END_DEPOSIT, endDeposit));
}

HandlerManagerImpl::~HandlerManagerImpl(void) {
    for_each(this->handlers->begin(), this->handlers->end(), [](const EventHandler * const handler) -> void {
        delete handler;
    });
    delete this->handlers;
}

void HandlerManagerImpl::runEventHandler(const Event event) const {
    for_each(this->handlers->begin(), this->handlers->end(), [&](const EventHandler * const handler) -> void {
        if (handler->isForEvent(event)) {
            handler->execute();
        }
    });
}

void HandlerManagerImpl::addEventHandler(const EventHandler * const handler) const {
    this->handlers->push_back(handler);
}
