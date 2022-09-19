/* Main library */
#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include "timers.h"
#include <semphr.h>

/* Communication library */
#include <SPI.h>

/* Sensor & Device library */
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

/* DHT sensor Pin setting */
#define DHT1PIN 2
#define DHT2PIN 3
#define DHTTYPE DHT11

/* DHT Task */
void TaskDHT11(void *pvParameters);

SemaphoreHandle_t xSerialSemaphore;

/* DHT sensor object */
DHT dht1(DHT1PIN, DHTTYPE);
// DHT_Unified dht1(DHT1PIN, DHTTYPE);
// DHT_Unified dht2(DHT2PIN, DHTTYPE);

/* DHT11 sensor data structure definition */
struct TEMP_HUMID {
    sensors_event_t temp;
    // sensors_event_t humd;
};

TEMP_HUMID place1;
// TEMP_HUMID place2;

void setup() {
    Serial.begin(115200);
    Serial.println(F("Arduino is rebooted!"));

    dht1.begin();
    // dht2.begin();

    if((xSerialSemaphore = xSemaphoreCreateMutex()) != NULL) {
        xSemaphoreGive((xSerialSemaphore));
    }

    // Task Creating
    xTaskCreate(TaskDHT11, "DHT11", 128, NULL, 1, NULL);
}

void loop() {}

void TaskDHT11(void *pvParameters __attribute__((unused))) {
    (void)pvParameters;

    dht1.begin();

    for(;;) {
        Serial.print("sensing temp...");

        if(xSemaphoreTake(xSerialSemaphore, (TickType_t)10) == pdTRUE) {
            Serial.println(place1.temp.temperature);
            xSemaphoreGive(xSerialSemaphore);
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for one second
    }
}