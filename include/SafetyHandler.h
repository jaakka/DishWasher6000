#ifndef SAFETYHANDLER_H
#define SAFETYHANDLER_H

#include "SensorHandler.h"
#include "RelayHandler.h"
#include "Memory.h"

enum class ErrorCode {
    Unknown,
    Flood,
    DoorOpenAndWashActive,
    Overheat
};

class SafetyHandler {
public:
    SafetyHandler(RelayHandler& relays, SensorHandler& sensors);
    void activateSafeMode(ErrorCode reason);
    bool safeModeIsActive() const;
    void safetyLoop();
    void emergencyShutdown();
    bool errorSavedInMemory() const;
    ErrorCode readLastRunErrorCode() const;

private:
    RelayHandler& relays_;
    SensorHandler& sensors_;
    bool safeModeActive_;
    bool verifySafeMode() const;
    Memory memory_;
};

#endif