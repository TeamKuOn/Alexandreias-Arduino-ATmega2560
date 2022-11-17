#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include "timers.h"

TimerHandle_t xSec;

// #define LED 13

/* Prototype Decleration of function */
void TaskA(void *pvParameters);
void TaskB(void *pvParameters);

// void TaskBlink(void *pvParameters);
// void TaskChecker(void *pvParameters);

void xTimerCallback(TimerHandle_t xTime);

// the setup function runs once when you press reset or power the board
void setup() {

    Serial.begin(115200);

    // while(!Serial) 
    //     ; // wait for serial port to connect. Needed for native USB, on
    //       // LEONARDO, MICRO, YUN, and other 32u4 based boards.
    // }

    xSec = xTimerCreate("Test", pdMS_TO_TICKS(1000), pdTRUE, (void *)0, xTimerCallback);

    xTimerStart(xSec, 0);

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

    // xTaskCreate(TaskBlink, "Blink", 128, NULL, 2, NULL);

    // xTaskCreate(TaskChecker, "Checker", 128, NULL, 1, NULL);
}

void loop() {}

void TaskA(void *pvParameters) { // This is a task.
    (void)pvParameters;

    for(;;) { // A Task shall never return or exit.
        Serial.println('A');
        vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for one second
    }
}

void TaskB(void *pvParameters) { // This is a task.
    (void)pvParameters;

    for(;;) {
        Serial.println('B');
        vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for one second
    }
}

// unsigned char led_state;

// void TaskBlink(void *pvParameters) {
//     (void)pvParameters;

//     pinMode(LED, OUTPUT);

//     for(;;) {
//         digitalWrite(LED, HIGH);
//         led_state = HIGH;
//         vTaskDelay(1000 / portTICK_PERIOD_MS);
//         digitalWrite(LED, LOW);
//         led_state = LOW;
//         vTaskDelay(1000 / portTICK_PERIOD_MS);
//     }
// }

// void TaskChecker(void *pvParameters) {
//     (void)pvParameters;

//     int value = analogRead(A0);
//     int i = 0;
//     for(;;) {

//         value = analogRead(A0);

//         Serial.println(value);
//         delay(100);
//         i++;

//         if(i == 30) {
//             if((value < 700) && (led_state == HIGH)) {
//                 Serial.println("くらい");
//                 i = 0;

//             } else if((value > 900) && (led_state == HIGH)) {
//                 Serial.println("明るすぎ！");
//                 i = 0;

//             } else {
//                 i = 0;
//             }
//         }

//         vTaskDelay(1);
//     }
// }

void xTimerCallback(TimerHandle_t xTime){
    Serial.println("Hello World ");
}
