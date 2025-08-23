#include "SensorHandler.h"
#include "pins.h"

SensorHandler::SensorHandler() : 
    quality(QUALITITY_SENSOR_PIN),
    door(DOOR_SENSOR_PIN),
    overheat(OVERHEAT_SENSOR_PIN),
    flood(FLOOD_SENSOR_PIN),
    level(LEVEL_SENSOR_PIN)
{}

bool SensorHandler::DoorIsOpen() const {
    return door.isOn();
}

bool SensorHandler::WaterQualityOk() const {
    return quality.isOn();
}

bool SensorHandler::OverheatDetected() const {
    return overheat.isOn();
}

bool SensorHandler::FloodDetected() const {
    return flood.isOn();
}

bool SensorHandler::WaterIsMaxLevel() const {
    return level.isOn();
}