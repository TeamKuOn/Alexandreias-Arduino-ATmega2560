# Arduino

# Devices

| Device                  | I/O            | Connection       | PIN(atmega2560)                           | Library name                                                                                                                         | 
| ----------------------- | -------------- | ---------------- | ----------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------ | 
| ADRead                  | Input / Output | Analog / Digital |                                           | --                                                                                                                                   | 
| AS5601_Mag_Encoder      | Input          | SPI              |                                           | --                                                                                                                                   | 
| MCP2515_CAN             | Output         | SPI              | SCK(52)<br>MOSI(51)<br>MISO(50)<br>SS(53) | [autowp / arduino-mcp2515](https://github.com/autowp/arduino-mcp2515)                                                                | 
| microSD_Interface       | Output         | SPI              | SCK(52)<br>MOSI(51)<br>MISO(50)<br>SS(53) | [arduino-libraries / SD](https://github.com/arduino-libraries/SD/tree/master/examples)                                               | 
| HWT905-TTL_IMU          | Input          | UART             | Tx1(18)<br>Rx1(19)                        | JY901.h on [WITMOTION / HWT905-TTL<br>](https://github.com/WITMOTION/HWT905-TTL)                                                     | 
| NEO-7M_GPS              | Input          | UART             | Tx2(16)<br>Rx2(17)                        | [mikalhart / TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus)                                                                  | 
| MS4525DO_Pitot          | Input          | I2C              | SDA<br>SCL                                | [bolderflight / ms4525do](https://github.com/bolderflight/ms4525do)                                                                  | 
| DHT11_Temp_Humid_sensor | Input          | Digital pin      | D2, D3                                    | [adafruit / DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library)                                                      | 
| INA_Current             | Input          | I2C              | SDA<br>SCL                                | [asukiaaa / INA226_asukiaaa](https://github.com/asukiaaa/INA226_asukiaaa)<br>or<br>[Zanduino / INA](https://github.com/Zanduino/INA) | 