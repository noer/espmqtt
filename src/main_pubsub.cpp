/* 
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h>

#define _TASK_MICRO_RES
#define _TASK_OO_CALLBACKS
#include <TaskScheduler.h>
#include "CTask.h"
Scheduler ts;

ESP8266WiFiMulti WifiMulti;
WiFiClient espClient;
PubSubClient mqtt(espClient);
WiFiEventHandler onConnectedHandler;
WiFiEventHandler onDisconnectedHandler;

CTask* tMQTTClient = new CTask(&ts, 100, []() {
    mqtt.loop();
});

CTask* tWiFiConnect = new CTask(&ts, 100, []() {
    if(WifiMulti.run() == WL_CONNECTED) {
        tWiFiConnect->disable();
    }
}, true);

static int count = 0;
CTask* tPubMsg = new CTask(&ts, 3000, []() {
    //if(WiFi.status() != WL_CONNECTED) {
        String msg = "Hello ";
        msg += count++;
        //Serial.printf("State before publish: %i\n", mqtt.state());
        mqtt.publish("noer/compass2", msg.c_str());
    //}
});

CTask* tMQTTConnect = new CTask(&ts, 100, []() {
    while (!mqtt.connected()) {
        if (mqtt.connect("CompassClient")) {
            Serial.printf("MQTT connected after %i ms\n", millis());
            mqtt.subscribe("noer/compass");
            tMQTTClient->restart();
            tPubMsg->restart();
        } else {
            Serial.printf("failed with state %i\n", mqtt.state());
            tMQTTConnect->restartDelayed(200 * TASK_MILLISECOND);
        }
    }
}, TASK_ONCE, false);

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);

    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }

    Serial.println();
    Serial.println("-----------------------");
}

String macToString(const unsigned char* mac) {
  char buf[20];
  snprintf(buf, sizeof(buf), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(buf);
}

void setup() {
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    WifiMulti.addAP("noers","JesusMySavior");

    onConnectedHandler = WiFi.onStationModeConnected([](const WiFiEventStationModeConnected& evt) {
        Serial.printf("Connected to the WiFi network: %s after %i ms\n", evt.ssid.c_str(), millis());
        tMQTTConnect->restart();
    });

    onDisconnectedHandler = WiFi.onStationModeDisconnected([](const WiFiEventStationModeDisconnected& evt) {
        Serial.printf("Disconnected to the WiFi network: %i\n", evt.reason);
        tPubMsg->disable();
        tMQTTClient->disable();
    });

    // uint8_t* ip = new uint8_t[4]{52, 13, 116, 147};
    // mqtt.setServer(ip, 1883);
    mqtt.setServer("public.mqtthq.com", 1883);
    mqtt.setCallback(callback);
}

void loop() {
    ts.execute();
}
 */