#include "ServiceImpl.h"
#include "MessageImpl.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define SSID "Android Gio"
#define PSWD "HellIfISay18"
#define PORT 80
#define STATUS_URI "/state"
#define DEPOSIT_URI "/deposit"
#define CONTENT_ERROR "Content cannot be correctly read"
#define FIELD_ERROR "One or more fields are missing"
#define TYPE_ERROR "One or more fields have an incorrect value type"
#define REQUEST_ERROR "The request could not be fullfilled"
#define SERVICE_URL "http://192.168.43.201:8080"

ServiceImpl::ServiceImpl(void) 
    : server(new ESP8266WebServer(PORT)), messageBox(new LinkedList<const Message *>()) {
    WiFi.begin(SSID, PSWD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    this->server->on(STATUS_URI, HTTPMethod::HTTP_GET, [&]() -> void {
        StaticJsonDocument<0> * const doc = new StaticJsonDocument<0>();
        this->messageBox->add(new MessageImpl(MessageType::READ, STATUS_URI, doc));
    });
    this->server->on(STATUS_URI, HTTPMethod::HTTP_PUT, [&]() -> void {
        StaticJsonDocument<26> * const doc = new StaticJsonDocument<26>();
        if (!deserializeJson(*doc, this->server->arg("plain")) != DeserializationError::Code::Ok) {
            if (!(*doc)["available"].isNull()) {
                if ((*doc)["available"].is<bool>()) {
                    this->messageBox->add(new MessageImpl(MessageType::MODIFY, STATUS_URI, doc));
                } else {
                    this->server->send(400, "text/plain", TYPE_ERROR);
                }
            } else {
                this->server->send(400, "text/plain", FIELD_ERROR);
            }
        } else {
            this->server->send(400, "text/plain", CONTENT_ERROR);
        }
    });
    this->server->on(DEPOSIT_URI, HTTPMethod::HTTP_PUT, [&]() -> void {
        StaticJsonDocument<30> * const doc = new StaticJsonDocument<30>();
        if (!deserializeJson(*doc, this->server->arg("plain")) != DeserializationError::Code::Ok) {
            if (!(*doc)["deposit"].isNull()) {
                if ((*doc)["deposit"].is<const char *>() && ((*doc)["deposit"].as<String>() == "begin"
                                                             || (*doc)["deposit"].as<String>() == "end")) {
                    this->messageBox->add(new MessageImpl(MessageType::MODIFY, DEPOSIT_URI, doc));
                } else {
                    this->server->send(400, "text/plain", TYPE_ERROR);
                }
            } else {
                this->server->send(400, "text/plain", FIELD_ERROR);
            }
        } else {
            this->server->send(400, "text/plain", CONTENT_ERROR);
        }
    });
    this->server->onNotFound([&]() -> void {
        this->server->send(404, "text/plain", REQUEST_ERROR);
    });
    this->server->begin();
}

ServiceImpl::~ServiceImpl(void) {
    this->server->stop();
    delete this->server;
    for (int i = 0; i < this->messageBox->size(); i++) {
        delete this->messageBox->get(i);
    }
    delete this->messageBox;
}

bool ServiceImpl::isMessageAvailable(void) const {
    this->server->handleClient();
    noInterrupts();
    bool isNotEmpty = this->messageBox->size() != 0;
    interrupts();
    return isNotEmpty;
}

const Message *ServiceImpl::receiveMessage(void) {
    noInterrupts();
    const Message *msg = this->messageBox->shift();
    interrupts();
    return msg;
}

String ServiceImpl::sendMessage(const MessageType type, const String resource, const JsonDocument &payload) const {
    if (type != MessageType::RESPONSE) {
        WiFiClient client;
        HTTPClient http;
        http.begin(client, String(SERVICE_URL) + resource);
        if (type == MessageType::READ) {
            http.addHeader("Content-Type", "text/plain");
            http.GET();
        } else if (type == MessageType::MODIFY) {
            http.addHeader("Content-Type", "application/json");
            String payloadString = "";
            serializeJson(payload, payloadString);
            http.PUT(payloadString);
        }
        http.end();
        return http.getString();
    } else if (!payload["success"].isNull() && payload["success"].as<bool>()) {
        JsonDocument messageBody = payload;
        messageBody.remove("success");
        String messageBodyString = "";
        serializeJson(messageBody, messageBodyString);
        this->server->send(200, "application/json", messageBodyString);
    } else {
        this->server->send(403, "text/plain", "");
    }
    return "";
}