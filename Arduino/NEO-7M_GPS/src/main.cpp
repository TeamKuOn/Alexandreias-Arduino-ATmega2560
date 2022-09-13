#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include <TinyGPS++.h>
#include "timers.h"

static const uint32_t GPSBand = 9600;

/* The TinyGPS++ object */
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
    gpsSerial.begin(GPSBand);

    Serial.println("GPS test....");


}

void loop() {}

    while(GpsSerial.available() > 0) {
        if(neo6m.encode(GpsSerial.read())) {
            Serial.println(
                "---------------------------------------------------");
            // getSensorsData();

            // Serial.print("Result: ");   Serial.println(GpsJson.Latitude);
            // Serial.print("Result: ");   Serial.println(GpsJson.Altitude);

            Serial.println(neo6m.location.lat(), 8);
            Serial.println(neo6m.location.lng(), 8);
            Serial.println(neo6m.altitude.kilometers());
            Serial.println(neo6m.hdop.value());
            dataAsBytToChar(GpsJson.HDOP, "HDOP", neo6m.hdop.value(),
                            neo6m.hdop.isValid()); // get HDOP
            Serial.println(GpsJson.HDOP);
            // GpsJson.Latitude = neo6m.location.lat();
            // Serial.println(latitude);
            // Serial.println(neo6m.location.lat(), 6);
            // Serial.println(neo6m.location.isValid());
            // Serial.println(neo6m.location.lat(), 6);
            // Serial.println(neo6m.location.lng(), 6);

            // delay(500);
        } else {
            //      Serial.println("GPS signal is not Valid...");
        }
    }
