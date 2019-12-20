#include "MessageParserImpl.h"
#include "Message.h"

// TODO: maybe use a bimap
MessageParserImpl::MessageParserImpl(void) {}

Message MessageParserImpl::parseStrToMsg(const String stringMessage) const {
    if (stringMessage == "A") {
        return Message::SET_TRASH_A;
    } else if (stringMessage == "B") {
        return Message::SET_TRASH_B;
    } else if (stringMessage == "C") {
        return Message::SET_TRASH_C;
    } else if (stringMessage == "K") {
        return Message::KEEP_OPEN;
    } else if (stringMessage == "O") {
        return Message::START_DEPOSIT;
    } else if (stringMessage == "E") {
        return Message::END_DEPOSIT;
    } else {
        return Message::EMPTY;
    }
}

String MessageParserImpl::parseMsgToStr(const Message message) const {
    if (message == Message::SET_TRASH_A) {
        return "A";
    } else if (message == Message::SET_TRASH_B) {
        return "B";
    } else if (message == Message::SET_TRASH_C) {
        return "C";
    } else if (message == Message::KEEP_OPEN) {
        return "K";
    } else if (message == Message::START_DEPOSIT) {
        return "S";
    } else if (message == Message::END_DEPOSIT) {
        return "E";
    } else {
        return "";
    }
}