/* Main Library */
// #include "Arduino.h"
// #include <Arduino_FreeRTOS.h>
// #include <semphr.h>
// #include "timers.h"

/* Device Library */
// #include "ms4525do.h"
// // #include <ArxTypeTraits.h>

// SemaphoreHandle_t xSerialSemaphore;

// void TaskPressure(void *pvParameters);

// bfs::Ms4525do presSensor;

// void setup() {
//     Serial.begin(115200);

//     Wire.begin();
//     Wire.setClock(400000);

//     if((xSerialSemaphore = xSemaphoreCreateMutex()) != NULL) {
//         xSemaphoreGive((xSerialSemaphore));
//     }

//     xTaskCreate(TaskPressure, "Pressure", 128, NULL, 1, NULL);
// }

// void loop() {}

// void TaskPressure(void *pvParameters) {
//     (void)pvParameters;

//     presSensor.Config(&Wire, 0x28, 1.0f, -1.0f);

//     for(;;) {

//         if(xSemaphoreTake(xSerialSemaphore, (TickType_t)10) == pdTRUE) {
//             Serial.println("Taking semaphore");

//             if(presSensor.Begin()) {
//                 Serial.print("Pressure: ");
//                 Serial.print(presSensor.pres_pa());

//                 Serial.print(" Temp: ");
//                 Serial.println(presSensor.die_temp_c());
//             }

//             xSemaphoreGive(xSerialSemaphore);
//         }
//         vTaskDelay(1);
//     }
// }

#include "Arduino.h"
#include "ms4525do.h"

/* * An MS4525DO object */
bfs::Ms4525do pres;

void setup() {
    /* Serial to display data */
    Serial.begin(9600);
    while(!Serial) {
    }
    Wire.begin();
    Wire.setClock(400000);
    /*
     * I2C address of 0x28, on bus 0, with a -1 to +1 PSI range
     */
    pres.Config(&Wire, 0x28, 1.0f, -1.0f);
    /* Starting communication with the pressure transducer */
    if(!pres.Begin()) {
        Serial.println("Error communicating with sensor");
        while(1) {
        }
    }
}

void loop() {
    /* Read the sensor */
    if(pres.Read()) {
        /* Display the data */
        Serial.print(pres.pres_pa(), 6);
        Serial.print("\t");
        Serial.print(pres.die_temp_c(), 6);
        Serial.print("\n");
    }
    delay(10);
}