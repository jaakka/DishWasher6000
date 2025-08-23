#ifndef SENSORHANDLER_H
#define SENSORHANDLER_H

#include "OnOffSensor.h"

class SensorHandler {

public:
    SensorHandler();
    bool DoorIsOpen() const;
    bool WaterQualityOk() const;
    bool OverheatDetected() const;
    bool FloodDetected() const;
    bool WaterIsMaxLevel() const;

private:
    OnOffSensor quality_, door_, overheat_, flood_, level_;
};

#endif