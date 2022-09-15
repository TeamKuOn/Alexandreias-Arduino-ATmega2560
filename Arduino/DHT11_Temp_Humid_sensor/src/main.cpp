// #include "Arduino.h"
// #include <Arduino_FreeRTOS.h>
// #include "timers.h"
// #include <Adafruit_Sensor.h>
// #include <DHT.h>
// #include <DHT_U.h>
// // #include <semphr.h>

// /* DHT sensor Pin setting */
// #define DHT1PIN 2
// #define DHT2PIN 3
// #define DHTTYPE DHT11

// /* DHT Task */
// void TaskDHT11(void *pvParameters);

// /* Timer interrupt setting */
// // TimerHandle_t xSec;

// // void xDHT11Callback(TimerHandle_t xTime);

// /* DHT sensor object */
// DHT dht1(DHT1PIN, DHTTYPE);
// // DHT_Unified dht1(DHT1PIN, DHTTYPE);
// // DHT_Unified dht2(DHT2PIN, DHTTYPE);

// /* DHT11 sensor data structure definition */
// struct TEMP_HUMID {
//     sensors_event_t temp;
//     // float temp = 0;
//     // float humid = 0;
// };

// TEMP_HUMID place1;
// // TEMP_HUMID place2;

// void setup() {
//     Serial.begin(115200);
//     Serial.println(F("Arduino is rebooted!"));

//     dht1.begin();
//     // dht2.begin();
//     float t = dht1.readTemperature();

//     // Task Creating
//     xTaskCreate(TaskDHT11, /* Task function. */
//                 "DHT11",   /* String with name of task. */
//                 128,       /* Stack size in bytes. */
//                 NULL,      /* Parameter passed as input of the task */
//                 1,         /* Priority of the task. */
//                 NULL);     /* Task handle. */

//     // sensor_t sensor;
//     // dht1.temperature().getSensor(&sensor);
//     // Serial.println(F("------------------------------------"));
//     // Serial.println(F("Temperature Sensor"));
//     // Serial.print(F("Sensor Type: "));
//     // Serial.println(sensor.name);
//     // Serial.print(F("Driver Ver:  "));
//     // Serial.println(sensor.version);
//     // Serial.print(F("Unique ID:   "));
//     // Serial.println(sensor.sensor_id);
//     // Serial.print(F("Max Value:   "));
//     // Serial.print(sensor.max_value);
//     // Serial.println(F("°C"));
//     // Serial.print(F("Min Value:   "));
//     // Serial.print(sensor.min_value);
//     // Serial.println(F("°C"));
//     // Serial.print(F("Resolution:  "));
//     // Serial.print(sensor.resolution);
//     // Serial.println(F("°C"));

//     // Timer Creating
//     // xSec = xTimerCreate("DHT11", pdMS_TO_TICKS(1000), pdTRUE, (void *)0,
//     // xDHT11Callback); xTimerStart(xSec, 0);
// }

// void loop() {}

// void TaskDHT11(void *pvParameters __attribute__((unused)) ) {
//     (void)pvParameters;

//     // float templeture;

//     dht1.begin();

//     for(;;) {
//         Serial.print("sensing temp...");
        
//         // Serial.println(dht1.read());
//         sensors_event_t event;
//         dht1.temperature().getEvent(&event);
//         // templeture = dht1.readTemperature();
//         Serial.print("place1 temp: ");
//         // Serial.println(place1.temp.temperature);
//         Serial.println(event.temperature);
//         // Serial.println(templeture);

//         vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for one second
//     }
// }

// // void xDHT11Callback(TimerHandle_t xTime){
// /*
//     place1
// */
// // place1.temp = dht1.temperature().getSensor(&sensor);
// // place1.humid = dht1.readTemperature();
// // sensors_event_t event;
// // place1.temp = dht1.temperature().getEvent(&event);
// // dht1.temperature().getEvent(&place1.temp);

// /*
//     place2
// */
// // place2.temp = dht2.temperature().getSensor(&sensor);
// // place2.humid = dht2.readTemperature();

// // Serial.print("place1 temp: ");  Serial.println(place1.temp.temperature);
// // Serial.print("place2 temp: ");  Serial.println(place2.temp);
// // }





