#include <Arduino_FreeRTOS.h>
#include <SPI.h>
#include <mcp2515.h>

#include "Arduino.h"
#include "timers.h"

/*
        Timer interrupt setting
*/
TimerHandle_t xMSec;

void xCANSendCallback(TimerHandle_t xTime);

/*
        CAN setting
*/
#define chopSelect 10

struct can_frame canMsg1;

MCP2515 mcp2515(chopSelect);

void setup() {
    Serial.begin(9600);
    Serial.println("Starting up");

    /* Timer Interrupt setting */
    xMSec = xTimerCreate("CANSend", pdMS_TO_TICKS(100), pdTRUE, (void *)0, xCANSendCallback);
    xTimerStart(xMSec, 0);

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
	
    Serial.println("Setup complete");
}

void loop() {}

void xCANSendCallback(TimerHandle_t xTime) { mcp2515.sendMessage(&canMsg1); }