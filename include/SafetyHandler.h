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
    void activateSafeMode(ErrorCode reason);
    bool safeModeIsActive() const;
    void safetyLoop();
    void emergencyShutdown();
    bool errorSavedInMemory() const;
    ErrorCode readLastRunErrorCode() const;

private:
    SensorHandler& sensors_;
    RelayHandler& relays_;
    bool safeModeActive_;
    bool verifySafeMode() const;
};

#endif