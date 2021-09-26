

struct DEV_TempSensor : Service::TemperatureSensor
{ // A standalone Temperature sensor

  SpanCharacteristic *temp; // reference to the Current Temperature Characteristic
  uint32_t timer = 0;
  // keep track of time since last update

  DEV_TempSensor() : Service::TemperatureSensor()
  { // constructor() method

    char c[64];
    double tempC = 999;

    for (uint8_t i = 0; i < 10; ++i) // try a few times to get a valid reading
    {
      tempC = mySensor.readTemperature();
      sprintf(c, "HTU21D Temperature - Constructor: %0.2fC\n", tempC); // log the reading
      LOG2(c);                                                         //verbose logging

      if (tempC < 101)
        break; //if the reading is sensible exit out of the loop
      delay(50);
    } // end for

    if (tempC > 100) // if result is invalid set result to be nonsensical - user can then tell something is wrong
    {
      tempC = 99;
    }

    temp = new Characteristic::CurrentTemperature(tempC); // instantiate the Current Temperature Characteristic
    temp->setRange(-50, 100);                             // expand the range from the HAP default of 0-100 to -50 to 100 to allow for negative temperatures

    sprintf(c, "HTU21D initial Temperature - end Constructor: %0.2fC\n", tempC);
    LOG1(c);

  } // end constructor

  void loop()
  {
    double tempC = 999;
    char c[64];

    if (millis() - timer > 5000)
    { // only sample every 5 seconds
      timer = millis();

      for (uint8_t i = 0; i < 10; ++i) // try a few times to get a valid reading
      {
        tempC = mySensor.readTemperature();
        sprintf(c, "HTU21D Temperature - Sensor Loop %0.2fC\n", tempC); // log the reading
        LOG2(c);                                                        //verbose logging

        if (tempC < 101)
          break; //if the reading is sensible exit out of the loop
        delay(50);
      } // end for

      if (tempC > 100)
      {
        tempC = temp->getVal();
      }

      if (abs(temp->getVal<double>() - tempC) > 0.5)
      {                      // only update temperature if change is more than 0.5C
        temp->setVal(tempC); // set the new temperature; this generates an Event Notification and also resets the elapsed time
        sprintf(c, "HTU21D Temperature Update: %0.2fC\n", tempC);
        LOG1(c);
      }
    } // end if timer

  } // loop
};

struct DEV_HumidSensor : Service::HumiditySensor
{
  SpanCharacteristic *humid;
  uint32_t timer = 0; // to set frequency of updates

  DEV_HumidSensor() : Service::HumiditySensor()
  { // constructor
    char c[64];
    double humidP = 999;

    for (uint8_t i = 0; i < 10; ++i) // try a few times to get a valid reading
    {
      humidP = mySensor.readHumidity();
      sprintf(c, "HTU21D Humidity - Constructor: %0.2f%%\n", humidP); // log the reading
      LOG2(c);                                                       //verbose logging

      if (humidP < 200)
        break; //if the reading is sensible exit out of the loop
      delay(50);
    } // end for




if (humidP > 200) // if result is invalid set result to be nonsensical - user can then tell something is wrong
    {
      humidP = 99;
    }

    humid = new Characteristic::CurrentRelativeHumidity(humidP);  // instantiate the Current Temperature Characteristic
    // temp->setRange(-50, 100);                             // expand the range from the HAP default of 0-100 to -50 to 100 to allow for negative temperatures

    sprintf(c, "HTU21D initial Humidity - end Constructor: %0.2f%%\n", humidP);
    LOG1(c);

  }   // end constructor

  void loop()
  {

    double humidP = 999;
    char c[64];

    if (millis() - timer > 5000)
    { // only sample every 5 seconds
      timer = millis();

      for (uint8_t i = 0; i < 10; ++i) // try a few times to get a valid reading
      {
        humidP = mySensor.readHumidity();

        sprintf(c, "HTU21D Humidity - Sensor Loop %0.2f%%\n", humidP); // log the reading
        LOG2(c);                                                      //verbose logging

        if (humidP < 200)
          break; //if the reading is sensible exit out of the loop
        delay(50);
      } // end for

      if (humidP > 200)
      {
        humidP = humid->getVal();
      }

      if (abs(humid->getVal<double>() - humidP) > 0.5)
      {                        // only update temperature if change is more than 0.5C
        humid->setVal(humidP); // set the new temperature; this generates an Event Notification and also resets the elapsed time
        sprintf(c, "HTU21D Temperature Update: %0.2f%%\n", humidP);
        LOG1(c);
      }

    } // end if millis

  } //end loop

}; // end struct DEV_HumidSensor