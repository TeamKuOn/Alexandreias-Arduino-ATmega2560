/* Main Library*/
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#include "Arduino.h"
#include "timers.h"

/* Prototype Decleration of function */
void TaskA(void *pvParameters);
void TaskB(void *pvParameters);

// void TaskBlink(void *pvParameters);
// void TaskChecker(void *pvParameters);

// void xTimerCallback(TimerHandle_t xTime);

// the setup function runs once when you press reset or power the board
void setup() {

    Serial.begin(115200);

    /*
        Now set up two tasks to run independently.

        xTaskCreate(Task function, 
                    String with name of task, 
                    Stack size in bytes, 
                    Parameter passed as input of the task, 
                    Priority of the task, 
                    Task handle);
    */

    xTaskCreate(TaskA, "TaskA", 128, NULL, 2, NULL);

    xTaskCreate(TaskB, "TaskB", 128, NULL, 1, NULL);

}

void loop() {}

void TaskSerialPrint(void *pvParameters) { // This is a task.
    (void)pvParameters;

    for(;;) { // A Task shall never return or exit.
        Serial.println('Hello World');
        vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for one second
    }
}

void TaskSerialWrite(void *pvParameters) { // This is a task.
    (void)pvParameters;

    float f = 135.291804;
    for(;;) {
        Serial.println(f);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for one second
    }
}

