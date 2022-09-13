#include "Arduino.h"
#include <TinyGPS++.h>

static const uint32_t GPSBand = 9600;

#define GPSSerial Serial1 // Tx1(18), Rx1(19)

void setup() {
    Serial.begin(115200);
    GPSSerial.begin(GPSBand);

    Serial.println("GPS test....");
}

// structure setting
struct gpsNeo6mJson {
    char Date[30];
    char Time[30];
    char Latitude[30];
    char Longitude[30];
    char Altitude[30];
    char HDOP[30];
};

void loop() {
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
}
