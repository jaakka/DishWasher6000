#include "SafetyHandler.h"

SafetyHandler::SafetyHandler(SensorHandler& sensors, RelayHandler& relays)
    : sensors_(sensors), relays_(relays), safeModeActive_(false) {}

void SafetyHandler::ActivateSafeMode(ErrorCode reason) {
    // Save error code later
    safeModeActive_ = true;
    relays_.ValveOff();
    relays_.PumpOff();
    relays_.WashOff();
    relays_.HeatOff();
    relays_.SoapOff();
    if(!VerifySafeMode()) {
        EmergencyShutdown();
    }
}

bool SafetyHandler::SafeModeIsActive() const {
    return safeModeActive_;
}

bool SafetyHandler::VerifySafeMode() const {
    if(relays_.ValveActive()) return false;
    if(relays_.PumpActive()) return false;
    if(relays_.WashActive()) return false;
    if(relays_.HeatActive()) return false;
    if(relays_.SoapActive()) return false;
    return true;
}

void SafetyHandler::EmergencyShutdown() {
    relays_.PowerOff();
}

void SafetyHandler::SafetyLoop() {
    if(sensors_.FloodDetected()) {
        ActivateSafeMode(ErrorCode::Flood);
    } else if (sensors_.OverheatDetected() && relays_.HeatActive()) {
        ActivateSafeMode(ErrorCode::Overheat);
    } else if (sensors_.DoorIsOpen() && relays_.PumpActive()) {
        ActivateSafeMode(ErrorCode::DoorOpenAndWashActive);
    }
}

bool SafetyHandler::ErrorSavedInMemory() const {
    // Add later error memory
    return false;
}

ErrorCode SafetyHandler::ReadLastRunErrorCode() const {
    // Add later error memory
    return ErrorCode::Unknown;    
}