#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include "timers.h"

SemaphoreHandle_t xSerialSemaphore;

void TaskDigitalRead(void *pvParameters);
void TaskAnalogRead(void *pvParameters);

void setup() { 
	Serial.begin(115200); 

	if ((xSerialSemaphore = xSemaphoreCreateMutex()) != NULL) {
            xSemaphoreGive((xSerialSemaphore));
        }

	xTaskCreate(TaskDigitalRead, "DigitalRead", 128, NULL, 1, NULL);

	xTaskCreate(TaskAnalogRead, "AnalogRead", 128, NULL, 1, NULL);
}

void loop() {}

void TaskDigitalRead(void *pvParameters) {
	uint8_t pushButton = 2;
	pinMode(pushButton, INPUT);

	for (;;) {
		int buttonState = digitalRead(pushButton);

		if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE ) {
			Serial.print("DigitalRead: ");
			Serial.println(buttonState);
			xSemaphoreGive( xSerialSemaphore );
		}

		vTaskDelay(1);
	}
}

void TaskAnalogRead(void *pvParameters) {
	for (;;) {
		int sensorValue = analogRead(A0);

		if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE ) {
			Serial.print("AnalogRead: ");
			xSemaphoreGive( xSerialSemaphore );
		}

		vTaskDelay(1000);
	}
}