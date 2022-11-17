/* Main library */
#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include "timers.h"
#include <semphr.h>

/* Communication library */
#include <SPI.h>

/* Sensor library */
#include <mcp2515.h>

SemaphoreHandle_t xSerialSemaphore;

typedef unsigned char ___u64Byte;

/* Task setting */
void TaskCANSend(void *pvParameters);
// void TaskCANReceive(void *pvParameters);

/* CAN setting */
#define chipSelect 53

/* Struct init */
struct can_frame canMsg1;
struct can_frame canMsg2;

/* Class init */
MCP2515 mcp2515(chipSelect);

void setup() {
    Serial.begin(115200);
    Serial.println("Starting up");

    if((xSerialSemaphore = xSemaphoreCreateMutex()) != NULL) {
        xSemaphoreGive((xSerialSemaphore));
    }

    /* Task setting */
    xTaskCreate(TaskCANSend, "CANSend", 2048, NULL, 1, NULL);
    // xTaskCreate(TaskCANReceive, "CANSend", 128, NULL, 1, NULL);

    mcp2515.reset();
    mcp2515.setBitrate(CAN_125KBPS);
    // mcp2515.setBitrate(CAN_500KBPS);
    mcp2515.setNormalMode();

    Serial.println("Setup complete");
}

void loop() {}

void double2Bytes(double double_variable, ___u64Byte bytes_temp[8]) {
    union {
        double d;
        ___u64Byte bytes[8];
    } thing;
    thing.d = double_variable;
    memcpy(bytes_temp, thing.bytes, 8);
}

void TaskCANSend(void *pvParameters) {
    /* MCP2515 setting */

    canMsg1.can_id = 0x0F6;
    canMsg1.can_dlc = 8;

    canMsg2.can_id = 0x0F7;
    canMsg2.can_dlc = 8;

    for(;;) {
        if(xSemaphoreTake(xSerialSemaphore, (TickType_t)10) == pdTRUE) {
            double data1 = 135.355414; // -> 0x40 0x5F 0x85 0x1F 0x9F 0x01 0x00 0x00
            Serial.println(data1);
            double2Bytes(data1, canMsg1.data);

            double data2 = 33.665608; // -> 0x40 0x5F 0x85 0x1F 0x9F 0x01 0x00 0x00
            Serial.println(data1);
            double2Bytes(data2, canMsg2.data);

            // Serial.println("Sending CAN message...");
            for(int i = 0; i < canMsg1.can_dlc; i++)
                Serial.print(canMsg1.data[i], HEX);
            Serial.println("");

            for(int i = 0; i < canMsg2.can_dlc; i++)
                Serial.print(canMsg2.data[i], HEX);
            Serial.println("");

            mcp2515.sendMessage(&canMsg1);
            mcp2515.sendMessage(&canMsg2);

            xSemaphoreGive(xSerialSemaphore);
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void TaskCANReceive(void *pvParameters) {

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

            xSemaphoreGive(xSerialSemaphore);
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
