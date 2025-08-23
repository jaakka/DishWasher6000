#include "RelayHandler.h"
#include "pins.h"

RelayHandler::RelayHandler() : 
    valve(VALVE_RELAY_PIN), 
    pump(PUMPOUT_RELAY_PIN), 
    wash(PUMPWASH_RELAY_PIN), 
    heat(HEATER_RELAY_PIN), 
    power(POWERCONTROL_RELAY_PIN), 
    soap(SOAPDOOR_RELAY_PIN)
{}

// Valve
void RelayHandler::ValveOn()    { valve.on(); }
void RelayHandler::ValveOff()   { valve.off(); }
bool RelayHandler::ValveActive() const { return valve.isActive(); }

// Pump
void RelayHandler::PumpOn()     { pump.on(); }
void RelayHandler::PumpOff()    { pump.off(); }
bool RelayHandler::PumpActive() const { return pump.isActive(); }

// Wash
void RelayHandler::WashOn()     { wash.on(); }
void RelayHandler::WashOff()    { wash.off(); }
bool RelayHandler::WashActive() const { return wash.isActive(); }

// Heat
void RelayHandler::HeatOn()     { heat.on(); }
void RelayHandler::HeatOff()    { heat.off(); }
bool RelayHandler::HeatActive() const { return heat.isActive(); }

// Soap
void RelayHandler::SoapOn()     { soap.on(); }
void RelayHandler::SoapOff()    { soap.off(); }
bool RelayHandler::SoapActive() const { return soap.isActive(); }

// Power
void RelayHandler::PowerOff()   { power.off(); }