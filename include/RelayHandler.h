#ifndef RELAYHANDLER_H
#define RELAYHANDLER_H

#include "Relay.h"

class SafetyHandler;

class RelayHandler {

public:
    RelayHandler();

    void addSafetyHandler(SafetyHandler* safetyHandler);

    void valveOn();
    void valveOff();
    bool valveActive() const;

    void pumpOn();
    void pumpOff();
    bool pumpActive() const;

    void washOn();
    void washOff();
    bool washActive() const;

    void heatOn();
    void heatOff();
    bool heatActive() const;

    void soapOn();
    void soapOff();
    bool soapActive() const;

    void powerOff();

private:
    Relay valve_, pump_, wash_, heat_, power_, soap_;
    SafetyHandler* safetyHandler_;
};

#endif