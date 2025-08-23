#include <Arduino.h>
#include "SafetyHandler.h"
#include "RelayHandler.h"
#include "SensorHandler.h"

RelayHandler relayHandler;
SensorHandler sensorHandler;
SafetyHandler safetyHandler(sensorHandler, relayHandler);

void setup() {
    relayHandler.AddSafetyHandler(&safetyHandler);
    relayHandler.SoapOn();
}

void loop() {
    safetyHandler.SafetyLoop();
}