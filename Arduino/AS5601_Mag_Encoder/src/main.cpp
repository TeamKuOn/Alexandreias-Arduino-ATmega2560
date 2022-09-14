#include <Arduino_FreeRTOS.h>
#include <Wire.h>
#include <stdint.h>

#include "Arduino.h"
#include "timers.h"

#define AS5600_AS5601_DEV_ADDRESS 0x36    // Register device address
#define AS5600_AS5601_REG_RAW_ANGLE 0x0C  // Register access address

void getMagData(void *pvParameters);

void setup() {
    // I2C init
    Wire.begin();
    Wire.setClock(400000);

    // Communication function init
    Serial.begin(115200);
    while (!Serial)
        ;

    xTaskCreate(getMagData, 'getMagData', 128, NULL, 1, NULL);
}

void loop() {}

void getMagData(void *pvParameters) {
    (void)pvParameters;

    for (;;) {
        // Read RAW_ANGLE value from encoder
        Wire.beginTransmission(AS5600_AS5601_DEV_ADDRESS);
        Wire.write(AS5600_AS5601_REG_RAW_ANGLE);
        Wire.endTransmission(false);
        Wire.requestFrom(AS5600_AS5601_DEV_ADDRESS, 2);

        uint16_t RawAngle = 0;
        RawAngle = ((uint16_t)Wire.read() << 8) & 0x0F00;
        RawAngle |= (uint16_t)Wire.read();
        // Raw angle value (0x0000~0x0FFF) is stored in RawAngle

        Serial.print("Raw angle value = ");
        Serial.println(RawAngle);
    }
}