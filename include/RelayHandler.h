#ifndef RELAYHANDLER_H
#define RELAYHANDLER_H

#include "Relay.h"

class SafetyHandler;

class RelayHandler {

public:
    RelayHandler();

    void AddSafetyHandler(SafetyHandler* safetyHandler);

    void ValveOn();
    void ValveOff();
    bool ValveActive() const;

    void PumpOn();
    void PumpOff();
    bool PumpActive() const;

    void WashOn();
    void WashOff();
    bool WashActive() const;

    void HeatOn();
    void HeatOff();
    bool HeatActive() const;

    void SoapOn();
    void SoapOff();
    bool SoapActive() const;

    void PowerOff();

private:
    Relay valve_, pump_, wash_, heat_, power_, soap_;
    SafetyHandler* safetyHandler_;
};

#endif