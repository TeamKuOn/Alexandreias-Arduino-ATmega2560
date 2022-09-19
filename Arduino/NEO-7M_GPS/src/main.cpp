/* Main library */
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#include "Arduino.h"
#include "timers.h"

/* Sensor library */
#include <TinyGPS++.h>

SemaphoreHandle_t xSerialSemaphore;
SemaphoreHandle_t xInterruptSemaphore;
SemaphoreHandle_t xVariableSemaphore;

static const uint32_t GPSBaud = 9600;

/* Task Settings */
void TaskCarPosition(void *pvParameters);

void interruptHandler();
/* The TinyGPS++ object */
TinyGPSPlus gpsInfo;
#define gpsSerial Serial2  // Rx -> Tx2(16), Tx -> Rx2(17)

// structure setting
struct NEO7M_GPS {
    // Date
    uint32_t year = 0;
    uint8_t month = 0;
    uint8_t day = 0;

    // Time
    uint8_t hour = 0;
    uint8_t minute = 0;
    uint8_t second = 0;

    // GPS position
    double lat = 0;
    double lng = 0;
    double altMeters = 0;

    // GPS hrizontal dilution of precision
    double hdop = 0;
};

// global variable
struct NEO7M_GPS carPosition;

void setup() {
    Serial.begin(115200);

    pinMode(2, INPUT_PULLUP);

    if ((xSerialSemaphore = xSemaphoreCreateMutex()) != NULL) {
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

    for (;;) {
        // if(xSemaphoreTake(xInterruptSemaphore, (TickType_t)10) == pdTRUE) {
        if (xSemaphoreTake(xSerialSemaphore, (TickType_t)10) == pdTRUE) {
            while (gpsSerial.available() > 0) {
                gpsInfo.encode(gpsSerial.read());
            }
            xSemaphoreGive(xSerialSemaphore);
        }
        // }

        Serial.println("---------------------------------------------------");

        if (xSemaphoreTake(xSerialSemaphore, (TickType_t)10) == pdTRUE) {
            carPosition.year = gpsInfo.date.year();
            carPosition.month = gpsInfo.date.month();
            carPosition.day = gpsInfo.date.day();

            carPosition.hour = gpsInfo.time.hour();
            carPosition.minute = gpsInfo.time.minute();
            carPosition.second = gpsInfo.time.second();

            carPosition.lat = gpsInfo.location.lat();
            carPosition.lng = gpsInfo.location.lng();
            carPosition.altMeters = gpsInfo.altitude.meters();
            carPosition.hdop = gpsInfo.hdop.value();

            xSemaphoreGive(xSerialSemaphore);
        }
        
        Serial.println(carPosition.year);
        Serial.println(carPosition.month);
        Serial.println(carPosition.day);

        Serial.println(carPosition.hour);
        Serial.println(carPosition.minute);
        Serial.println(carPosition.second);

        Serial.println(carPosition.lat, 8);
        Serial.println(carPosition.lng, 8);
        Serial.println(carPosition.altMeters);
        Serial.println(carPosition.hdop);

        vTaskDelay(1);
    }
}