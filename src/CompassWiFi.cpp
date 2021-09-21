#include "CompassWiFi.h"

CompassWiFi::CompassWiFi(Scheduler* aS) : Task(100 * TASK_MILLISECOND, TASK_FOREVER, aS, true) {
    WiFi.mode(WIFI_STA);
    WifiMulti.addAP(DEFAULT_SSID, DEFAULT_PASSPHRASE);

    // wifiConnectHandler = WiFi.onStationModeGotIP([this](const WiFiEventStationModeGotIP& event){
    //     Serial.printf("WIFI connected after %i ms\n", millis());
    //     // for(auto& cb : connectCBs) {
    //     //     Serial.println("Call CBs");
    //     //     cb();
    //     // }
    //     //tMQTTConnect->restart();
    //     //restart();
    // });

    // wifiDisconnectHandler = WiFi.onStationModeDisconnected([this](const WiFiEventStationModeDisconnected& event){
    //     Serial.println("Disconnected from Wi-Fi.");
        
    //     // Make sure not to connect MQTT while WiFi is disconnected
    //     //tMQTTConnect->disable();
    //     // for(auto& cb : disconnectCBs) {
    //     //     cb();
    //     // }
    //     restartDelayed(TASK_SECOND);
    // });
}

CompassWiFi::~CompassWiFi() {
    disable();
}

bool CompassWiFi::Callback() {
    if(WifiMulti.run() == WL_CONNECTED) {
        disable();
    }
    return true;
}

void CompassWiFi::onConnect(const std::function<void(void)> cb) {
    connectCBs.push_back(cb);
}

void CompassWiFi::onDisconnect(const std::function<void(void)> cb) {
    disconnectCBs.push_back(cb);
}