#include "OnOffSensor.h"
#include <Arduino.h>

OnOffSensor::OnOffSensor(int pin) : pin_(pin) {
    pinMode(pin_, INPUT); 
}

bool OnOffSensor::isOn() const {
    return digitalRead(pin_) == HIGH;
}