#include "ServiceImpl.h"
#include "MessageImpl.h"

#define SSID "TIM-28166177"
#define PSWD "cnipXwHhGF2dGXaP4nI4dcjL"
#define PORT 80

ServiceImpl::ServiceImpl(void) : server(new ESP8266WebServer(PORT)) {
    WiFi.begin(SSID, PSWD);
    Serial.println("Connecting to the internet");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi is now connected with IP address: " + WiFi.localIP());
    this->server->begin();
}

ServiceImpl::~ServiceImpl(void) {
    this->server->stop();
    delete this->server;
}

bool ServiceImpl::isMessageAvailable(void) const {
    return true;
}

const Message *ServiceImpl::receiveMessage(void) const {
    return nullptr;
}

void ServiceImpl::sendMessage(const MessageType type, const int code, const DynamicJsonDocument payload) const {
    
}