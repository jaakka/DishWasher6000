#ifndef SENSORHANDLER_H
#define SENSORHANDLER_H

#include "OnOffSensor.h"
#include "TemperatureSensor.h"

class SensorHandler {

public:
    SensorHandler();
    bool doorIsOpen() const;
    bool waterQualityOk() const;
    bool overheatDetected() const;
    bool floodDetected() const;
    bool waterIsMaxLevel() const;
    // void loop();
    // float getTemperature() const;

private:
    OnOffSensor quality_, door_, overheat_, flood_, level_;
    // TemperatureSensor temperature_;
};

#endif