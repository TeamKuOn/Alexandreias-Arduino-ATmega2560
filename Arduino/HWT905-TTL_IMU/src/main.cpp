#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include "timers.h"
#include <Wire.h>
#include <JY901.h>

struct IMU {
	float accX = 0;
	float accY = 0;
	float accZ = 0;
};


void setup() {
	Serial.begin(115200);
}