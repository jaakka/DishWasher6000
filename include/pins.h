#ifndef WIRING_H
#define WIRING_H

#include <Arduino.h>

// Pin definitions
#define VALVE_RELAY_PIN 6 // Tested ok
#define PUMPOUT_RELAY_PIN 5 // Tested ok
#define PUMPWASH_RELAY_PIN 7 // Tested ok
#define HEATER_RELAY_PIN 4 // Tested ok
#define SOAPDOOR_RELAY_PIN 13 // Tested ok

// Dishwasher need 230v to use this relay
#define POWERCONTROL_RELAY_PIN 9 // VR HOLD

#define DOOR_SENSOR_PIN A2
#define FLOOD_SENSOR_PIN A4
#define OVERHEAT_SENSOR_PIN A3
#define LEVEL_SENSOR_PIN A5
#define DIGITAL_TEMP_SENSOR_PIN 12
#define QUALITITY_SENSOR_PIN A0 // ANALOG
#define DIGITAL_QUALITY_SENSOR_PIN A1

#define ENCODER_RIGHT_PIN 3
#define ENCODER_LEFT_PIN 2
#define ENCODER_BUTTON_PIN A6

#define WLAN_RX 10
#define WLAN_TX 11

#define LCD_TX 8
#define LCD_RX -1 // -1 means not used

#endif