# HS Environmental Sensor
HomeSpan Powered, Homekit Compatible Temperature and Humidity Sensor for ESP32 with the Arduino framework.

With thanks to the [HomeSpan](https://github.com/HomeSpan) project.


This is an implementation of [HomeSpan TempSensor I2C](https://github.com/HomeSpan/TempSensorI2C) modified for HTU21D i2c sensor.

Wrangling of the sensor thanks to [SparkFun](https://github.com/sparkfun/HTU21D_Breakout)


**Overview:

Based on a ESP32 DoItV2 Development board.
HTU21D Humidity and Temperature sensor - i2c
2 10k resistors.

Connections:
| GPIO | Connection|
| ---- | ------------- |
| 2 | Onboard LED |
|  0   | Onboard Button (also used for program upload) |
| 21 | SDA |
| 22 | SCL |



Tie the SDA and SCL lines HIGH (+3.3v) with the 10k Resistors.
    This dramatically improved the reliability of reading the sensor.








