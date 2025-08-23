#include "SensorHandler.h"
#include "pins.h"

SensorHandler::SensorHandler() : 
    quality_(QUALITITY_SENSOR_PIN),
    door_(DOOR_SENSOR_PIN),
    overheat_(OVERHEAT_SENSOR_PIN),
    flood_(FLOOD_SENSOR_PIN),
    level_(LEVEL_SENSOR_PIN)
    //,temperature_()
{}

bool SensorHandler::doorIsOpen() const {
    return door_.isOn();
}

bool SensorHandler::waterQualityOk() const {
    return quality_.isOn();
}

bool SensorHandler::overheatDetected() const {
    return overheat_.isOn();
}

bool SensorHandler::floodDetected() const {
    return flood_.isOn();
}

bool SensorHandler::waterIsMaxLevel() const {
    return level_.isOn();
}

// void SensorHandler::loop() {
//     temperature_.loop();
// }

// float SensorHandler::getTemperature() const {
//     return temperature_.getTemperature();
// }