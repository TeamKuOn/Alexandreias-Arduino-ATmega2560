#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include "timers.h"
#include <INA226_asukiaaa.h>

/*
        Timer interrupt setting
*/
TimerHandle_t xMSec;

void xINA226Callback(TimerHandle_t xTime);

/*
        INA226 setting
*/
const uint16_t ina226calib = INA226_asukiaaa::calcCalibByResistorMilliOhm(2); // Max 5120 milli ohm
// const uint16_t ina226calib = INA226_asukiaaa::calcCalibByResistorMicroOhm(2000);
INA226_asukiaaa voltCurrMeter(INA226_ASUKIAAA_ADDR_A0_GND_A1_GND, ina226calib);

struct INA226Data {
		int16_t voltage = 0;
		int16_t current = 0;
		int16_t power   = 0;
};

INA226Data batteryUnit;

void setup() {
	Serial.begin(115200);

	xMSec = xTimerCreate("xMSec", pdMS_TO_TICKS(1000), pdTRUE, (void *)0, xINA226Callback);
	xTimerStart(xMSec, 0);
}

void loop() {}


void xINA226Callback(TimerHandle_t xTime){
    voltCurrMeter.readMV(&batteryUnit.voltage);
    voltCurrMeter.readMA(&batteryUnit.current);
    voltCurrMeter.readMW(&batteryUnit.power);
}