#ifndef SAFETYHANDLER_H
#define SAFETYHANDLER_H

#include "SensorHandler.h"
#include "RelayHandler.h"

enum class ErrorCode {
    Unknown,
    Flood,
    DoorOpenAndWashActive,
    Overheat
};

class SafetyHandler {
public:
    SafetyHandler(SensorHandler& sensors, RelayHandler& relays);
    void ActivateSafeMode(ErrorCode reason);
    bool SafeModeIsActive() const;
    void SafetyLoop();
    void EmergencyShutdown();
    bool ErrorSavedInMemory() const;
    ErrorCode ReadLastRunErrorCode() const;

private:
    SensorHandler& sensors_;
    RelayHandler& relays_;
    bool safeModeActive_;
    bool VerifySafeMode() const;
};

#endif