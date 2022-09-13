#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include "timers.h"

SemaphoreHandle_t xSerialSemaphore;

void TaskDigitalRead(void *pvParameters);
void TaskAnalogRead(void *pvParameters);

void void setup() { 
	Serial.begin(115200); 

	xTaskCreate(TaskDigitalRead, "DigitalRead", 128, NULL, 1, NULL);

	xTaskCreate(TaskAnalogRead, "AnalogRead", 128, NULL, 1, NULL);
}

void loop() {}

void TaskDigitalRead(void *pvParameters) {
	pinMode(13, OUTPUT);
	for (;;) {
		digitalWrite(13, HIGH);
		vTaskDelay(1000);
		digitalWrite(13, LOW);
		vTaskDelay(1000);
	}
}

void TaskAnalogRead(void *pvParameters) {
	for (;;) {
		int sensorValue = analogRead(A0);
		Serial.println(sensorValue);
		vTaskDelay(1000);
	}
}