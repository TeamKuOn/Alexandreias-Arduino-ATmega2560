/*
 * main.cpp
 */
#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

TimerHandle_t xMsec;

DHT dht(DHTPIN, DHTTYPE);

struct TEMP_HUMID {
    float temp;
    float humid;
};

void xDHT11Callback(TimerHandle_t);

void setup() {
    Serial.begin(115200);
    Serial.println(F("DHT11 test!"));

    dht.begin();

    TEMP_HUMID place1;
    TEMP_HUMID place2;

    xMsec = xTimerCreate("DHT11", pdMS_TO_TICKS(1000), pdTRUE, (void *)0, xDHT11Callback);
    xTimerStart(xMsec, 0);
}

void loop() {}

void xDHT11Callback(TimerHandle_t xTime){
    // place1 
    place1.temp = dht.readHumidity();
    place1.humid = dht.readTemperature();

    // place2 
    place2.temp = dht.readHumidity();
    place2.humid = dht.readTemperature();

}
