#include "SensorHandler.h"
#include "pins.h"

SensorHandler::SensorHandler() : 
    quality_(QUALITITY_SENSOR_PIN),
    door_(DOOR_SENSOR_PIN),
    overheat_(OVERHEAT_SENSOR_PIN),
    flood_(FLOOD_SENSOR_PIN),
    level_(LEVEL_SENSOR_PIN)
{}

bool SensorHandler::DoorIsOpen() const {
    return door_.isOn();
}

bool SensorHandler::WaterQualityOk() const {
    return quality_.isOn();
}

bool SensorHandler::OverheatDetected() const {
    return overheat_.isOn();
}

bool SensorHandler::FloodDetected() const {
    return flood_.isOn();
}

bool SensorHandler::WaterIsMaxLevel() const {
    return level_.isOn();
}