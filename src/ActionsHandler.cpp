#include "ActionsHandler.h"
#include "config.h"

ActionsHandler::ActionsHandler(SensorHandler &sensors, RelayHandler &relays) : relays_(relays),
                                                                               sensors_(sensors)
{
    current_action_ = ActiveAction::noAction;
    action_time_ = 0;
}

// Returns remaining time
int ActionsHandler::addSoap()
{
    if (current_action_ == ActiveAction::noAction)
    {
        if (!sensors_.doorIsOpen())
        {
            action_time_ = SOAP_TIME_IN_S;
            current_action_ = ActiveAction::addSoap;
            last_time = millis();
            relays_.soapOn();
            Serial.println("soap started.");
        }
        else
        {
            Serial.println("Soap waiting door close.");
        }
    }
    else if (current_action_ == ActiveAction::addSoap)
    {
        if (millis() - last_time >= 1000)
        {
            last_time += 1000;
            if (action_time_ > 0)
            {
                action_time_--;
            }
            else
            {
                Serial.println("soap ok.");
                relays_.soapOff();
                current_action_ = ActiveAction::noAction;
            }
        }
    }
    return action_time_;
}

int ActionsHandler::fillWater()
{
    if (current_action_ == ActiveAction::noAction)
    {
        action_max_time_ = WATER_MAX_FILLTIME_IN_S;
        action_time_ = memory_.load(MemoryPos::waterFillTime);
        current_action_ = ActiveAction::fillWater;
        last_time = millis();
        relays_.valveOn();
        Serial.println("water fill started.");
    }
    else if (current_action_ == ActiveAction::fillWater)
    {
        if (millis() - last_time >= 1000)
        {
            last_time += 1000;
            if (sensors_.waterIsMaxLevel())
            {
                relays_.valveOff();
                current_action_ = ActiveAction::noAction;
                action_time_ = 0;
                Serial.println("water fill ok");
                int timeUsed = 0;

                memory_.save(MemoryPos::waterFillTime, (WATER_MAX_FILLTIME_IN_S - action_max_time_), true);
            }
            else
            {
                if (action_time_ > 0)
                {
                    action_time_--;
                    action_max_time_--;
                }
                else
                {
                    if (!sensors_.waterIsMaxLevel() && action_max_time_ > 0)
                    {
                        action_time_ = action_max_time_;
                        return action_time_; // Skip next code
                    }
                    // Error water level not detected
                    Serial.println("water fill error, max time reached!");
                    relays_.valveOff();

                    // Need stop program ?!?!?
                    //current_action_ = ActiveAction::noAction;
                }
            }
        }
    }
    return action_time_;
}

int ActionsHandler::wash(int wash_time_in_minutes)
{
    if (current_action_ == ActiveAction::noAction)
    {
        action_time_ = wash_time_in_minutes * 60;
        current_action_ = ActiveAction::wash;
        last_time = millis();
        relays_.washOn();
        Serial.println("wash started.");
    }
    else if (current_action_ == ActiveAction::wash)
    {
        if (millis() - last_time >= 1000)
        {
            last_time += 1000;

            if (action_time_ > 0)
            {
                if (sensors_.doorIsOpen())
                {
                    if (relays_.washActive())
                    {
                        relays_.washOff();
                        Serial.println("Wash action waiting door close.");
                    }
                }
                else
                {
                    if (!relays_.washActive())
                    {
                        relays_.washOn();
                        Serial.println("Wash action continue. Door closed.");
                    }
                    action_time_--;
                }
            }
            else
            {

                Serial.println("wash ok.");
                relays_.washOff();
                current_action_ = ActiveAction::noAction;
            }
        }
    }
    return action_time_;
}

int ActionsHandler::emptyWater()
{
    if (current_action_ == ActiveAction::noAction)
    {
        action_time_ = WATER_EMPTY_TIME_IN_S;
        current_action_ = ActiveAction::emptyWater;
        last_time = millis();
        relays_.pumpOn();
        Serial.println("water empty started.");
    }
    else if (current_action_ == ActiveAction::emptyWater)
    {
        if (millis() - last_time >= 1000)
        {
            last_time += 1000;

            if (action_time_ > 0)
            {
                action_time_--;
            }
            else
            {

                Serial.println("water empty ok.");
                relays_.pumpOff();
                current_action_ = ActiveAction::noAction;
            }
        }
    }
    return action_time_;
}

int ActionsHandler::heatHot()
{

    return action_time_;
}

int ActionsHandler::heatWarm()
{

    return action_time_;
}

ActiveAction ActionsHandler::currentAction()
{
    return current_action_;
}