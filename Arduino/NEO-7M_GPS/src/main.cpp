/* Main library */
#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include "timers.h"
#include <semphr.h>

/* Sensor library */
#include <TinyGPS++.h>

SemaphoreHandle_t xSerialSemaphore;
SemaphoreHandle_t xInterruptSemaphore;

static const uint32_t GPSBaud = 9600;

/* Task Settings */
void TaskCarPosition(void *pvParameters);

void interruptHandler();
/* The TinyGPS++ object */
TinyGPSPlus gpsInfo;
#define gpsSerial Serial2 // Rx -> Tx2(16), Tx -> Rx2(17)

// structure setting
struct NEO7M_GPS {
    char date[30] = "";
    char time[30] = "";
    char latitude[30] = "";
    char longitude[30] = "";
    char altitude[30] = "";
    char hddp[30] = "";
};

// global variable
struct NEO7M_GPS carPosition;

void setup() {
    Serial.begin(115200);

    pinMode(2, INPUT_PULLUP);

    if((xSerialSemaphore = xSemaphoreCreateMutex()) != NULL) {
        xSemaphoreGive((xSerialSemaphore));
    }

    // if((xInterruptSemaphore = xSemaphoreCreateBinary()) != NULL) {
    //     attachInterrupt(digitalPinToInterrupt(2), interruptHandler, FALLING);
    // }

    xTaskCreate(TaskCarPosition, "TaskCarPosition", 1000, NULL, 1, NULL);

    Serial.println("GPS test....");
}

void loop() {}

void interruptHandler() { xSemaphoreGiveFromISR(xInterruptSemaphore, NULL); }

void TaskCarPosition(void *pvParameters) {
    gpsSerial.begin(GPSBaud);

    for(;;) {

        // if(xSemaphoreTake(xInterruptSemaphore, (TickType_t)10) == pdTRUE) {
            if(xSemaphoreTake(xSerialSemaphore, (TickType_t)10) == pdTRUE) {
                while(gpsSerial.available() > 0) {
                    gpsInfo.encode(gpsSerial.read());
                }
                xSemaphoreGive(xSerialSemaphore);
            }
        // }


        Serial.println("---------------------------------------------------");

        Serial.println(gpsInfo.location.lat(), 8);
        Serial.println(gpsInfo.location.lng(), 8);
        Serial.println(gpsInfo.altitude.kilometers());
        Serial.println(gpsInfo.hdop.value());



        vTaskDelay(1);
    }
}