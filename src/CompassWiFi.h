#pragma once

#include <ESP8266WiFiMulti.h>
#include <vector>
#include <functional>

#define _TASK_MICRO_RES
#define _TASK_OO_CALLBACKS
#include <TaskSchedulerDeclarations.h>

#define DEFAULT_SSID        "noers"
#define DEFAULT_PASSPHRASE  "JesusMySavior"
//#define DEFAULT_SSID        "CompassOTA"
//#define DEFAULT_PASSPHRASE  "CommitYourWayPS37:5"

class CompassWiFi : Task {
private:
    ESP8266WiFiMulti WifiMulti;
    WiFiEventHandler wifiConnectHandler;
    WiFiEventHandler wifiDisconnectHandler;
    std::vector<std::function<void(void)>> connectCBs;
    std::vector<std::function<void(void)>> disconnectCBs;

public:
    CompassWiFi(Scheduler* aS);
    ~CompassWiFi();
    bool Callback();
    void onConnect(const std::function<void(void)> cb);
    void onDisconnect(const std::function<void(void)> cb);
};