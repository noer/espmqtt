#pragma once

#include <ESP8266WiFiMulti.h>
#include <Ticker.h>

#include "config.h"

class CompassWiFi {
private:
    ESP8266WiFiMulti WifiMulti;
    WiFiEventHandler wifiConnectHandler;
    WiFiEventHandler wifiDisconnectHandler;
    Ticker wifiReconnectTimer;
    void connectToWifi();

public:
    CompassWiFi();
    ~CompassWiFi();
};