#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include "pins.h"
#include <OneWire.h>
#include <DallasTemperature.h>

class TemperatureSensor : public Sensor {
  public:
    TemperatureSensor();
    void loop() override;
    bool getSensorState() override { return false; };
    float getSensorValue() override;

  private:
    OneWire oneWire;              
    DallasTemperature dallasTemperature;
    float temperatures[10];
    float calcAverageTemperature();
    void addTemperature(float temp);
};

#endif