#include "RelayHandler.h"
#include "SafetyHandler.h" 
#include "pins.h"

RelayHandler::RelayHandler() : 
    valve_(VALVE_RELAY_PIN), 
    pump_(PUMPOUT_RELAY_PIN), 
    wash_(PUMPWASH_RELAY_PIN), 
    heat_(HEATER_RELAY_PIN), 
    power_(POWERCONTROL_RELAY_PIN), 
    soap_(SOAPDOOR_RELAY_PIN)
{}

// Valve
void RelayHandler::valveOn() { 
    if(safetyHandler_ && !safetyHandler_->safeModeIsActive()) {
        valve_.on(); 
    }
}
void RelayHandler::valveOff()   { valve_.off(); }
bool RelayHandler::valveActive() const { return valve_.isActive(); }

// Pump
void RelayHandler::pumpOn() { 
    if(safetyHandler_ && !safetyHandler_->safeModeIsActive()) {
        pump_.on(); 
    }
}
void RelayHandler::pumpOff()    { pump_.off(); }
bool RelayHandler::pumpActive() const { return pump_.isActive(); }

// Wash
void RelayHandler::washOn() { 
    if(safetyHandler_ && !safetyHandler_->safeModeIsActive()) {
        wash_.on(); 
    }
}
void RelayHandler::washOff()    { wash_.off(); }
bool RelayHandler::washActive() const { return wash_.isActive(); }

// Heat
void RelayHandler::heatOn() { 
    if(safetyHandler_ && !safetyHandler_->safeModeIsActive()) {
        heat_.on(); 
    }
}
void RelayHandler::heatOff()    { heat_.off(); }
bool RelayHandler::heatActive() const { return heat_.isActive(); }

// Soap
void RelayHandler::soapOn() { 
    if(safetyHandler_ && !safetyHandler_->safeModeIsActive()) {
        soap_.on(); 
    }
}
void RelayHandler::soapOff()    { soap_.off(); }
bool RelayHandler::soapActive() const { return soap_.isActive(); }

// Power
void RelayHandler::powerOff()   { power_.off(); }

void RelayHandler::addSafetyHandler(SafetyHandler* safetyHandler) {
    safetyHandler_ = safetyHandler;
}