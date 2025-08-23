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
void RelayHandler::ValveOn() { 
    if(!safetyHandler_ || !safetyHandler_->SafeModeIsActive()) {
        valve_.on(); 
    }
}
void RelayHandler::ValveOff()   { valve_.off(); }
bool RelayHandler::ValveActive() const { return valve_.isActive(); }

// Pump
void RelayHandler::PumpOn() { 
    if(!safetyHandler_ || !safetyHandler_->SafeModeIsActive()) {
        pump_.on(); 
    }
}
void RelayHandler::PumpOff()    { pump_.off(); }
bool RelayHandler::PumpActive() const { return pump_.isActive(); }

// Wash
void RelayHandler::WashOn() { 
    if(!safetyHandler_ || !safetyHandler_->SafeModeIsActive()) {
        wash_.on(); 
    }
}
void RelayHandler::WashOff()    { wash_.off(); }
bool RelayHandler::WashActive() const { return wash_.isActive(); }

// Heat
void RelayHandler::HeatOn() { 
    if(!safetyHandler_ || !safetyHandler_->SafeModeIsActive()) {
        heat_.on(); 
    }
}
void RelayHandler::HeatOff()    { heat_.off(); }
bool RelayHandler::HeatActive() const { return heat_.isActive(); }

// Soap
void RelayHandler::SoapOn() { 
    if(!safetyHandler_ || !safetyHandler_->SafeModeIsActive()) {
        soap_.on(); 
    }
}
void RelayHandler::SoapOff()    { soap_.off(); }
bool RelayHandler::SoapActive() const { return soap_.isActive(); }

// Power
void RelayHandler::PowerOff()   { power_.off(); }

void RelayHandler::AddSafetyHandler(SafetyHandler* safetyHandler) {
    safetyHandler_ = safetyHandler;
}