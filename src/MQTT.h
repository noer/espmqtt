#pragma once

#include <Ticker.h>
#include <AsyncMqttClient.h>
#include <ESP8266WiFiMulti.h>
#include "CompassWiFi.h"
#include <functional>

class MQTT {
private:
    CompassWiFi* wifi = nullptr;
    AsyncMqttClient mqttClient;
    Ticker mqttReconnectTimer;

    WiFiEventHandler wifiConnectHandler;
    WiFiEventHandler wifiDisconnectHandler;

    std::function<void(void)> connectCb = nullptr;
    
    void onMqttConnect();
    void onMqttDisconnect();
    void onMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);

public:
    MQTT();
    ~MQTT();
    void setConnectCb(std::function<void(void)> cb);
    void publish(String topic, String msg);
};