/*
 * main.cpp
 */
#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"
#include "timers.h"

#define DHT1PIN 2
#define DHT2PIN 3
#define DHTTYPE DHT11

TimerHandle_t xSec;

void xDHT11Callback(TimerHandle_t xTime);
struct TEMP_HUMID {
    float temp = 0;
    float humid = 0;
};

void xDHT11Callback(TimerHandle_t);

DHT dht1(DHT1PIN, DHTTYPE);
DHT dht2(DHT2PIN, DHTTYPE);

TEMP_HUMID place1;
TEMP_HUMID place2;

void setup() {
    Serial.begin(115200);
    Serial.println(F("DHT11 test!"));

    dht1.begin();
    dht2.begin();

    xSec = xTimerCreate("DHT11", pdMS_TO_TICKS(1000), pdTRUE, (void *)0, xDHT11Callback);
    xTimerStart(xSec, 0);
}

void loop() {}

void xDHT11Callback(TimerHandle_t xTime){
    // place1 
    place1.temp = dht1.readHumidity();
    // place1.humid = dht1.readTemperature();

    // place2 
    place2.temp = dht2.readHumidity();
    // place2.humid = dht2.readTemperature();

    Serial.print("place1 temp: ");  Serial.println(place1.temp);
    Serial.print("place2 temp: ");  Serial.println(place2.temp);
}
