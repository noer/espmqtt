#include "CompassWiFi.h"

CompassWiFi::CompassWiFi() {
    WiFi.mode(WIFI_STA);
    WifiMulti.addAP(DEFAULT_SSID0, DEFAULT_PASSPHRASE0);
    WifiMulti.addAP(DEFAULT_SSID1, DEFAULT_PASSPHRASE1);
    WifiMulti.addAP(DEFAULT_SSID2, DEFAULT_PASSPHRASE2);

    wifiConnectHandler = WiFi.onStationModeGotIP([this](const WiFiEventStationModeGotIP& event){
        Serial.printf("WIFI connected after %i ms\n", millis());
    });

    wifiDisconnectHandler = WiFi.onStationModeDisconnected([this](const WiFiEventStationModeDisconnected& event){
        Serial.println("Disconnected from Wi-Fi.");
        wifiReconnectTimer.attach_ms_scheduled(100, [this]() {
            connectToWifi();
        });
    });

    wifiReconnectTimer.attach_ms_scheduled(100, [this]() {
        connectToWifi();
    });

}

CompassWiFi::~CompassWiFi() {
    WiFi.mode(WIFI_OFF);
    wifi_fpm_set_sleep_type (LIGHT_SLEEP_T);
    WiFi.forceSleepBegin(); //<-- saves like 100mA!
}

void CompassWiFi::connectToWifi() {
    if(WifiMulti.run() == WL_CONNECTED) {
        wifiReconnectTimer.detach();
    }
}
