#include <Arduino_FreeRTOS.h>

#include "Arduino.h"
#include "ms4525do.h"
#include "timers.h"

bfs::Ms4525do presSensor;

void setup() {
    Serial.begin(115200);

    Wire.begin();
    Wire.setClock(400000);

    xTaskCreate(TaskPressure, "Pressure", 128, NULL, 1, NULL);
}

void loop() {}

void TaskPressure(void *pvParameters) {
    (void)pvParameters;

    presSensor.Config(&Wire, 0x28, 1.0f, -1.0f);

    for (;;) {
        if (presSensor.Begin()) {
            Serial.print("Pressure: ");
            Serial.print(presSensor.pres_pa());

            Serial.print(" Temp: ");
            Serial.println(presSensor.die_temp_c());
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
    }
}