#include <MQTT.h>

MQTT::MQTT() {
    wifiConnectHandler = WiFi.onStationModeGotIP([this](const WiFiEventStationModeGotIP& evt) {
        Serial.println("Connecting to MQTT...");
        mqttClient.connect();
    });
    wifiDisconnectHandler = WiFi.onStationModeDisconnected([this](const WiFiEventStationModeDisconnected& evt) {
        Serial.println("Disconnected from Wi-Fi.");
        mqttReconnectTimer.detach(); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
    });

    mqttClient.onConnect([this](bool sessionPresent) {
        onMqttConnect();
    });
    mqttClient.onDisconnect([this](AsyncMqttClientDisconnectReason reason) {
        onMqttDisconnect();
    });
    mqttClient.onMessage([this](char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total){
        onMessage(topic, payload, properties, len, index, total);
    });
    mqttClient.setServer("public.mqtthq.com", 1883);

    wifi = new CompassWiFi();
}

MQTT::~MQTT() {
    delete wifi;
}

void MQTT::onMqttConnect() {
    Serial.printf("MQTT connected after %i ms\n", millis());
    mqttClient.subscribe("noer/compass", 2);
    if(connectCb) {
        connectCb();
    }
}

void MQTT::onMqttDisconnect() {
    Serial.println("Disconnected from MQTT.");

    //tPubMsg->disable();
    if (WiFi.isConnected()) {
        mqttReconnectTimer.once(2, [this]() {
            mqttClient.connect();
        });
    }
}

void MQTT::onMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
    Serial.println("Publish received.");
    Serial.print("  payload: ");
    Serial.println(payload);
}

void MQTT::setConnectCb(std::function<void(void)> cb) {
    connectCb = cb;
}

void MQTT::publish(String topic, String msg) {
    mqttClient.publish(topic.c_str(), 0, true, msg.c_str());
}
