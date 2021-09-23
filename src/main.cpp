#include <Arduino.h>
#include <MQTT.h>

#define _TASK_MICRO_RES
#define _TASK_OO_CALLBACKS
#include <TaskScheduler.h>
#include "CTask.h"
Scheduler ts;

MQTT* mqtt;

static int count = 0;
CTask* tPubMsg = new CTask(&ts, 10000, []() {
    String msg = "Hello ";
    msg += count++;
    mqtt->publish("noer/compass2", msg);
}, 10, false);

void setup() {
    Serial.begin(115200);

    mqtt = new MQTT();
    mqtt->setConnectCb([]() {
        tPubMsg->restart();
    });
}

void loop() {
    ts.execute();
}
