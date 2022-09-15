#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include "timers.h"
#include <TinyGPS++.h>

static const uint32_t GPSBand = 9600;

/* Task Settings */
void TaskCarPosition(void *pvParameters);

/* The TinyGPS++ object */
TinyGPSPlus gpsInfo;
#define gpsSerial Serial1 // Tx1(18), Rx1(19)

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
NEO7M_GPS carPosition;

void setup() {
    Serial.begin(115200);


    xTaskCreate(TaskCarPosition, "TaskCarPosition", 1000, NULL, 1, NULL);

    Serial.println("GPS test....");
}

void loop() {}

void TaskCarPosition(void *pvParameters) {
    gpsSerial.begin(GPSBand);

    for(;;) {

        while(gpsSerial.available() > 0) {
            if(gpsInfo.encode(gpsSerial.read())) {
                Serial.println("---------------------------------------------------");

                Serial.println(gpsInfo.location.lat(), 8);
                Serial.println(gpsInfo.location.lng(), 8);
                Serial.println(gpsInfo.altitude.kilometers());
                Serial.println(gpsInfo.hdop.value());

            } else {
                // Serial.println("GPS signal is not Valid...");
            }
        }
    }
}