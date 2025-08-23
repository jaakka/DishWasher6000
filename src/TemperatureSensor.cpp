#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor() : oneWire(DIGITAL_TEMP_SENSOR_PIN), dallasTemperature(&oneWire) {
    dallasTemperature.begin(); 
}

void TemperatureSensor::loop() {
    dallasTemperature.requestTemperatures();
    addTemperature(dallasTemperature.getTempCByIndex(0));
}

float TemperatureSensor::getSensorValue() {
    //y = 1.4263x - 14.558
    return 1.4263 * calcAverageTemperature() - 14.558;
}

float TemperatureSensor::calcAverageTemperature() {
    float sum = 0;
    for(int i = 0; i < 10; i++) {
        sum += temperatures[i];
    }
    return sum / 10;
}

void TemperatureSensor::addTemperature(float temp) {
    for(int i = 0; i < 9; i++) {
        temperatures[i] = temperatures[i + 1];
    }
    temperatures[9] = temp;
}