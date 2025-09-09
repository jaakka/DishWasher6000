#ifndef ACTIONSHANDLER_H
#define ACTIONSHANDLER_H

#include "SensorHandler.h"
#include "RelayHandler.h"
#include "Memory.h"

enum class ActiveAction {
    noAction,
    addSoap,
    wash,
    heat,
    fillWater,
    emptyWater,
    checkWater
};

class ActionsHandler {
public:
    ActionsHandler(SensorHandler& sensors, RelayHandler& relays);
    int addSoap();
    int wash(int wash_time_in_minutes); // Returns remaining time in seconds.
    int heatWarm();
    int heatHot();
    int fillWater();
    int emptyWater();
    int checkWaterQuality(int target_quality);
    ActiveAction currentAction();

private:
    SensorHandler& sensors_;
    RelayHandler& relays_;
    int action_time_;
    int action_max_time_;
    ActiveAction current_action_;
    Memory memory_;
    unsigned long last_time;
};

#endif