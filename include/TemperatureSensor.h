#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include "pins.h"
#include <OneWire.h>
#include <DallasTemperature.h>

class TemperatureSensor {
  public:
    TemperatureSensor();
    void loop();
    float getTemperature() const;

  private:
    OneWire oneWire;              
    DallasTemperature dallasTemperature;
    float temperatures[10];
    float calcAverageTemperature() const;
    void addTemperature(float temp);
};

#endif