#include "ActionsHandler.h"
#include "config.h"

ActionsHandler::ActionsHandler(SensorHandler& sensors, RelayHandler& relays) :
    relays_(relays),
    sensors_(sensors)
{
    current_action_ = ActiveAction::noAction;
    action_time_ = 0;
}

// Returns remaining time
int ActionsHandler::addSoap() {
    if(current_action_ == ActiveAction::noAction) {
        action_time_ = SOAP_TIME_IN_S;
        current_action_ = ActiveAction::addSoap;
        last_time = millis();
        relays_.soapOn();
    } else if(current_action_ == ActiveAction::addSoap) {
        if (millis() - last_time >= 1000) {
            last_time += 1000;
            if (action_time_ > 0) {
                action_time_--;
            } else {
                relays_.soapOff();
                current_action_ = ActiveAction::noAction;
            }
        }
    }
    return action_time_;
}

int ActionsHandler::wash() {
    relays_.washOn();
    return 0;
}

ActiveAction ActionsHandler::currentAction() { 
    return current_action_; 
}