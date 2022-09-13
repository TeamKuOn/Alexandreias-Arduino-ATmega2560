#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include "timers.h"
#include <SPI.h>
#include <SD.h>

const int chipSelect = 53;

File sampleFile;

/* Timer interrupt setting */
TimerHandle_t xMSec;

void xWriteSDCallback(TimerHandle_t xTime);

void setup() {
	Serial.begin(115200);

    xMSec = xTimerCreate("microSD", pdMS_TO_TICKS(100), pdTRUE, (void *)0, xWriteSDCallback);
    xTimerStart(xMSec, 0);
}

void loop() {}

void xWriteSDCallback(TimerHandle_t xTime){
	sampleFile = SD.open("sample.txt", FILE_WRITE);
	sampleFile.println("testing 1, 2, 3.");
    sampleFile.close();
}