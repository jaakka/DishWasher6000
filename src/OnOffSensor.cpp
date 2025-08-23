#include "OnOffSensor.h"
#include <Arduino.h>

OnOffSensor::OnOffSensor(int pin) : sensor_pin(pin) {
    pinMode(sensor_pin, INPUT); 
}

bool OnOffSensor::isOn() const {
    return digitalRead(sensor_pin) == HIGH;
}