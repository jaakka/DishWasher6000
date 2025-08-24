#include "SafetyHandler.h"

SafetyHandler::SafetyHandler(SensorHandler& sensors, RelayHandler& relays)
    : sensors_(sensors), relays_(relays) {
        safeModeActive_ = false;
    }

void SafetyHandler::activateSafeMode(ErrorCode reason) {
    // Save error code later
    safeModeActive_ = true;
    relays_.valveOff();
    relays_.pumpOff();
    relays_.washOff();
    relays_.heatOff();
    relays_.soapOff();
    if(!verifySafeMode()) {
        emergencyShutdown();
    }
}

bool SafetyHandler::safeModeIsActive() const {
    return safeModeActive_;
}

bool SafetyHandler::verifySafeMode() const {
    if(relays_.valveActive()) return false;
    if(relays_.pumpActive()) return false;
    if(relays_.washActive()) return false;
    if(relays_.heatActive()) return false;
    if(relays_.soapActive()) return false;
    return true;
}

void SafetyHandler::emergencyShutdown() {
    relays_.powerOff();
}

void SafetyHandler::safetyLoop() {
    if(sensors_.floodDetected()) {
        activateSafeMode(ErrorCode::Flood);
    } else if (sensors_.overheatDetected() && relays_.heatActive()) {
        activateSafeMode(ErrorCode::Overheat);
    } else if (sensors_.doorIsOpen() && relays_.washActive()) {
        activateSafeMode(ErrorCode::DoorOpenAndWashActive);
    }
}

bool SafetyHandler::errorSavedInMemory() const {
    // Add later error memory
    return false;
}

ErrorCode SafetyHandler::readLastRunErrorCode() const {
    // Add later error memory
    return ErrorCode::Unknown;    
}