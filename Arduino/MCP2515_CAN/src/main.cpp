#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include "timers.h"
#include <SPI.h>
#include <mcp2515.h>

/*
        Task setting
*/
// void TaskCANSend(void *pvParameters);
void TaskCANReceive(void *pvParameters);

/*
        Timer interrupt setting
*/
// TimerHandle_t xMSec;

// void xCANSendCallback(TimerHandle_t xTime);

/*
        CAN setting
*/
#define chopSelect 10

struct can_frame canMsg1;

MCP2515 mcp2515(chopSelect);

void setup() {
    Serial.begin(115200);
    Serial.println("Starting up");

    /* Task setting */
    // xTaskCreate(TaskCANSend, "CANSend", 128, NULL, 1, NULL);
    xTaskCreate(TaskCANReceive, "CANSend", 128, NULL, 1, NULL);

    /* Timer Interrupt setting */
    // xMSec = xTimerCreate("CANSend", pdMS_TO_TICKS(100), pdTRUE, (void *)0,
    // xCANSendCallback); xTimerStart(xMSec, 0);

    Serial.println("Setup complete");
}

void loop() {}

void TaskCANSend(void *pvParameters) {
    /* MCP2515 setting */
    mcp2515.reset();
    mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
    mcp2515.setNormalMode();

    canMsg1.can_id = 0x0F6;
    canMsg1.can_dlc = 8;
    canMsg1.data[0] = 0x8E;
    canMsg1.data[1] = 0x87;
    canMsg1.data[2] = 0x32;
    canMsg1.data[3] = 0xFA;
    canMsg1.data[4] = 0x26;
    canMsg1.data[5] = 0x8E;
    canMsg1.data[6] = 0xBE;
    canMsg1.data[7] = 0x86;

    for(;;) {
        Serial.println("Sending CAN message...");
        mcp2515.sendMessage(&canMsg1);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void TaskCANReceive(void *pvParameters) {
    mcp2515.reset();
    mcp2515.setBitrate(CAN_125KBPS);
    mcp2515.setNormalMode();

    for(;;) {
        if(mcp2515.readMessage(&canMsg1) == MCP2515::ERROR_OK) {
            Serial.print("ID: ");
            Serial.print(canMsg1.can_id, HEX);
            Serial.print(" DLC: ");
            Serial.print(canMsg1.can_dlc, DEC);
            Serial.print(" DATA: ");
            for(int i = 0; i < canMsg1.can_dlc; i++) {
                Serial.print(canMsg1.data[i], HEX);
                Serial.print(" ");
            }
            Serial.println();
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
