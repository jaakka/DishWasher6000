#include <Arduino.h>
#include "SafetyHandler.h"
#include "RelayHandler.h"
#include "SensorHandler.h"
#include "ActionsHandler.h"

RelayHandler relayHandler;
SensorHandler sensorHandler;
SafetyHandler safetyHandler(sensorHandler, relayHandler);
ActionsHandler actionsHandler(sensorHandler, relayHandler);

enum class Program {
    NoProgram,
    Eco,
    Normal,
    Super
};

int time = 1;
int program_step = 0;
Program program = Program::Eco;

void EcoProgram() {
    switch (program_step)
    {
        case 0: {
            int time = actionsHandler.addSoap();
            if (time == 0 && actionsHandler.currentAction() == ActiveAction::noAction) {
                program_step++;
            }
        }
        break;
        
        case 1:
            delay(1000);
            program_step++;
        break;

        case 2:
            time = actionsHandler.addSoap();
            if (time == 0 && actionsHandler.currentAction() == ActiveAction::noAction) {
                program_step++;
            }
        break;
            
        case 3:
            relayHandler.pumpOn();
        break;
    }
}

void BasicProgram() {
    
}

void SuperProgram() {
    
}

void setup() {
    relayHandler.addSafetyHandler(&safetyHandler);
}

void loop() {
    safetyHandler.safetyLoop();
    switch (program)
    {
        case Program::Eco:
            EcoProgram();
        break;
    
        case Program::Normal:
            BasicProgram();
        break;
        
        case Program::Super:
            SuperProgram();
        break;
    }
}