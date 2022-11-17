/* Main Library*/
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#include "Arduino.h"
#include "timers.h"

/* Communicatoin Library*/
#include <Wire.h>

/* Device Library*/
#include <INA226_asukiaaa.h>

SemaphoreHandle_t xSerialSemaphore;

/* Task setting */
void TaskINA226(void *pvParameters);

/* INA226 setting */
const uint16_t ina226calib = INA226_asukiaaa::calcCalibByResistorMilliOhm(2);  // Max 5120 milli ohm

// const uint16_t ina226calib =
// INA226_asukiaaa::calcCalibByResistorMicroOhm(2000);

/* Class init */
INA226_asukiaaa voltCurrMeter(INA226_ASUKIAAA_ADDR_A0_GND_A1_GND, ina226calib);

struct INA226Data {
    int16_t voltage = 0;
    int16_t current = 0;
    int16_t power = 0;
};

struct INA226Data batteryUnit;

void setup() {
    Serial.begin(115200);

    if ((xSerialSemaphore = xSemaphoreCreateMutex()) != NULL) {
        xSemaphoreGive((xSerialSemaphore));
    }

    xTaskCreate(TaskINA226, "TaskINA226", 128, NULL, 1, NULL);
}

void loop() {}

void TaskINA226(void *pvParameters) {
    for (;;) {
        if (xSemaphoreTake(xSerialSemaphore, (TickType_t)10) == pdTRUE) {
            voltCurrMeter.readMV(&batteryUnit.voltage);
            voltCurrMeter.readMA(&batteryUnit.current);
            voltCurrMeter.readMW(&batteryUnit.power);

			xSemaphoreGive(xSerialSemaphore);
        }

        vTaskDelay(1);
    }
}