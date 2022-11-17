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
#define gpsSerial Serial2 // Rx -> Tx2(16), Tx -> Rx2(17)

// structure setting
struct NEO7M_GPS {
    // Date
    int year = 0;
    int month = 0;
    int day = 0;

    // Time
    uint8_t hour = 0;
    uint8_t minute = 0;
    uint8_t second = 0;

    // GPS position
    double lat = 0;
    double lng = 0;
    double altMeters = 0;
    double degree = 0;
    double speedkmph = 0;

    // GPS hrizontal dilution of precision
    double hdop = 0;
};


struct SerialMesg {
    char Date[40] = "";
    char Time[40] = "";
    
    // // Accelaration XYZ
    // char accX[20] = "";
    // char accY[20] = "";
    // char accZ[20] = "";

    // GPS position
    char lat[20] = "";
    char lng[20] = "";
    char altMeters[20] = "";
    char degree[20] = "";
    char speedkmph[20] = "";

    // GPS hrizontal dilution of precision
    char hdop[20] = "";

        // Battery
    char voltage[20] = "";
    char current[20] = "";
    char power[20] = "";

};


// global variable
struct NEO7M_GPS carPosition;
struct SerialMesg Mesg4Raspi;

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


        if (xSemaphoreTake(xSerialSemaphore, (TickType_t)10) == pdTRUE) {
            carPosition.hour = gpsInfo.time.hour();
            carPosition.minute = gpsInfo.time.minute();
            carPosition.second = gpsInfo.time.second();
            carPosition.lat = gpsInfo.location.lat();
            carPosition.lng = gpsInfo.location.lng();
            carPosition.altMeters = gpsInfo.altitude.meters();
            carPosition.degree = gpsInfo.course.deg();
            carPosition.speedkmph = gpsInfo.speed.kmph();
            carPosition.hdop = gpsInfo.hdop.value();            

            sprintf(Mesg4Raspi.Date, "gps.date:%04d-%02d-%02d", carPosition.year, carPosition.month, carPosition.day);
            Serial.println(Mesg4Raspi.Date);

            sprintf(Mesg4Raspi.Time, "gps.time:%02d:%02d:%02d", carPosition.hour, carPosition.minute, carPosition.second);
            Serial.println(Mesg4Raspi.Time);

            sprintf(Mesg4Raspi.lat, "gps.lat:%f", carPosition.lat);
            Serial.println(Mesg4Raspi.lat);

            sprintf(Mesg4Raspi.lng, "gps.lng:%f", carPosition.lng);
            Serial.println(Mesg4Raspi.lng);

            sprintf(Mesg4Raspi.altMeters, "gps.altM:%f", carPosition.altMeters);
            Serial.println(Mesg4Raspi.altMeters);

            sprintf(Mesg4Raspi.degree, "gps.degree:%f", carPosition.degree);
            Serial.println(Mesg4Raspi.altMeters);

            sprintf(Mesg4Raspi.speedkmph, "gps.speedkmph:%f", carPosition.speedkmph);
            Serial.println(Mesg4Raspi.altMeters);

            sprintf(Mesg4Raspi.hdop, "gps.hdop:%f", carPosition.hdop);
            Serial.println(Mesg4Raspi.hdop);


            xSemaphoreGive(xSerialSemaphore);
        }

        // if(xSemaphoreTake(xSerialSemaphore, (TickType_t)10) == pdTRUE) {
        //     Serial.println(carPosition.year);
        //     Serial.println(carPosition.month);
        //     Serial.println(carPosition.day);

        //     Serial.println(carPosition.hour);
        //     Serial.println(carPosition.minute);
        //     Serial.println(carPosition.second);

        //     Serial.println(carPosition.lat, 8);
        //     Serial.println(carPosition.lng, 8);
        //     Serial.println(carPosition.altMeters);
        //     Serial.println(carPosition.hdop);

        //     xSemaphoreGive(xSerialSemaphore);
        // }

        vTaskDelay(1);
    }
}