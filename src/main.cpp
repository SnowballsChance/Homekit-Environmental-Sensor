/*
MIT License

Copyright (c) 2021 SnowballsChance

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

/*

Libraries:
Arduino: https://www.arduino.cc/
HomeSpan: https://github.com/HomeSpan
HTU21D: https://github.com/sparkfun/HTU21D_Breakout


*/


/*

!! Shamelessly plagiarised and only slightly modified from: https://github.com/HomeSpan/TempSensorI2C

*/

#include <Arduino.h>
#include <Wire.h>
#include "SparkFunHTU21D.h"
HTU21D mySensor;

#include "HomeSpan.h"
#include "DEV_Identify.h"
#include "DEV_Sensors.h"

char sNumber[18] = "11:11:11:11:11:11";  // global

void setup()
{
  Serial.begin(115200);

  for (int i = 0; i < 17; ++i)
  {
    sNumber[i] = WiFi.macAddress()[i];
  }
  sNumber[17] = '\0';

  Wire.begin(SDA, SCL);
  mySensor.begin(Wire);

  homeSpan.setStatusPin(2);
  homeSpan.setControlPin(0);
  homeSpan.setLogLevel(2);
  homeSpan.begin(Category::Bridges, "Environmental Sensor"); 

  new SpanAccessory();
  new DEV_Identify("Environmental Sensor", "Snowball's Chance ", sNumber, "HS Sensors", "0.1a", 10);
  new Service::HAPProtocolInformation();
  new Characteristic::Version("1.1.0");

  new SpanAccessory();
  new DEV_Identify("Temperature Sensor", "Snowball's Chance", sNumber, "HomeSpan Temperature Sensor", "0.1a", 0);
  new DEV_TempSensor();

new SpanAccessory();
  new DEV_Identify("Humidity Sensor", "Snowball's Chance", sNumber, "HomeSpan Humididty Sensor", "0.1a", 0);
  new DEV_HumidSensor();


} // end of setup()

//////////////////////////////////////

void loop()
{

  homeSpan.poll();

} // end of loop()

//////////////////////////////////////
