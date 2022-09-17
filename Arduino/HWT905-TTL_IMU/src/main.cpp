#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include "JY901.h"
#include "timers.h"
#include <Wire.h>

SemaphoreHandle_t xSerialSemaphore;

/* Task Settings */
void TaskIMU(void *pvParameters);

/* HWT905-TTL settings */
#define imuSerial Serial1 // Rx(green) -> Tx2(18), Tx(yellow) -> Rx1(19)

struct IMU {
    float accX = 0;
    float accY = 0;
    float accZ = 0;
};

IMU carAcc;

void setup() {
    Serial.begin(115200);

    if((xSerialSemaphore = xSemaphoreCreateMutex()) != NULL) {
        xSemaphoreGive((xSerialSemaphore));
    }

    xTaskCreate(TaskIMU, "TaskIMU", 128, NULL, 1, NULL);
}

void loop() {}

void TaskIMU(void *pvParameters) {
    imuSerial.begin(115200);

    for(;;) {
        if(xSemaphoreTake(xSerialSemaphore, (TickType_t)10) == pdTRUE) {
            while(imuSerial.available()) {
                JY901.CopeSerialData(imuSerial.read());
            }
        }

        carAcc.accX = (float)JY901.stcAcc.a[0] / 32768 * 16;
        carAcc.accY = (float)JY901.stcAcc.a[1] / 32768 * 16;
        carAcc.accZ = (float)JY901.stcAcc.a[2] / 32768 * 16;

        Serial.print("Acc:");
        Serial.print(carAcc.accX);
        Serial.print(" ");
        Serial.print(carAcc.accY);
        Serial.print(" ");
        Serial.println(carAcc.accZ);

        xSemaphoreGive(xSerialSemaphore);

        vTaskDelay(1);

        // Serial.print("Time:20");
        // Serial.print(JY901.stcTime.ucYear);
        // Serial.print("-");
        // Serial.print(JY901.stcTime.ucMonth);
        // Serial.print("-");
        // Serial.print(JY901.stcTime.ucDay);
        // Serial.print(" ");
        // Serial.print(JY901.stcTime.ucHour);
        // Serial.print(":");
        // Serial.print(JY901.stcTime.ucMinute);
        // Serial.print(":");
        // Serial.println((float)JY901.stcTime.ucSecond +
        // (float)JY901.stcTime.usMiliSecond / 1000);

        // Serial.print("Acc:");
        // Serial.print((float)JY901.stcAcc.a[0] / 32768 * 16);
        // Serial.print(" ");
        // Serial.print((float)JY901.stcAcc.a[1] / 32768 * 16);
        // Serial.print(" ");
        // Serial.println((float)JY901.stcAcc.a[2] / 32768 * 16);

        // Serial.print("Gyro:");
        // Serial.print((float)JY901.stcGyro.w[0] / 32768 * 2000);
        // Serial.print(" ");
        // Serial.print((float)JY901.stcGyro.w[1] / 32768 * 2000);
        // Serial.print(" ");
        // Serial.println((float)JY901.stcGyro.w[2] / 32768 * 2000);

        // Serial.print("Angle:");
        // Serial.print((float)JY901.stcAngle.Angle[0] / 32768 * 180);
        // Serial.print(" ");
        // Serial.print((float)JY901.stcAngle.Angle[1] / 32768 * 180);
        // Serial.print(" ");
        // Serial.println((float)JY901.stcAngle.Angle[2] / 32768 * 180);

        // Serial.print("Mag:");
        // Serial.print(JY901.stcMag.h[0]);
        // Serial.print(" ");
        // Serial.print(JY901.stcMag.h[1]);
        // Serial.print(" ");
        // Serial.println(JY901.stcMag.h[2]);

        // Serial.print("Pressure:");
        // Serial.print(JY901.stcPress.lPressure);
        // Serial.print(" ");
        // Serial.println((float)JY901.stcPress.lAltitude / 100);

        // Serial.print("DStatus:");
        // Serial.print(JY901.stcDStatus.sDStatus[0]);
        // Serial.print(" ");
        // Serial.print(JY901.stcDStatus.sDStatus[1]);
        // Serial.print(" ");
        // Serial.print(JY901.stcDStatus.sDStatus[2]);
        // Serial.print(" ");
        // Serial.println(JY901.stcDStatus.sDStatus[3]);

        // Serial.print("Longitude:");
        // Serial.print(JY901.stcLonLat.lLon / 10000000);
        // Serial.print("Deg");
        // Serial.print((double)(JY901.stcLonLat.lLon % 10000000) / 1e5);
        // Serial.print("m Lattitude:");
        // Serial.print(JY901.stcLonLat.lLat / 10000000);
        // Serial.print("Deg");
        // Serial.print((double)(JY901.stcLonLat.lLat % 10000000) / 1e5);
        // Serial.println("m");

        // Serial.print("GPSHeight:");
        // Serial.print((float)JY901.stcGPSV.sGPSHeight / 10);
        // Serial.print("m GPSYaw:");
        // Serial.print((float)JY901.stcGPSV.sGPSYaw / 10);
        // Serial.print("Deg GPSV:");
        // Serial.print((float)JY901.stcGPSV.lGPSVelocity / 1000);
        // Serial.println("km/h");

        // Serial.print("SN:");
        // Serial.print(JY901.stcSN.sSVNum);
        // Serial.print(" PDOP:");
        // Serial.print((float)JY901.stcSN.sPDOP / 100);
        // Serial.print(" HDOP:");
        // Serial.print((float)JY901.stcSN.sHDOP / 100);
        // Serial.print(" VDOP:");
        // Serial.println((float)JY901.stcSN.sVDOP / 100);

        // Serial.println("");
    }
}
