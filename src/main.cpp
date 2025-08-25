#include <Arduino.h>
#include "SafetyHandler.h"
#include "RelayHandler.h"
#include "SensorHandler.h"
#include "ActionsHandler.h"
#include "UserControl.h"
#include "LcdHandler.h"
#include "ViewHandler.h"

RelayHandler relayHandler;
SensorHandler sensorHandler;
SafetyHandler safetyHandler(sensorHandler, relayHandler);
ActionsHandler actionsHandler(sensorHandler, relayHandler);
UserControl userControl;
LcdHandler lcdHandler;
ViewHandler viewHandler(lcdHandler);

enum class Program {
    NoProgram,
    Eco,
    Normal,
    Super
};

int time = 1;
int program_step = 0;
int printed_test_time = 0;

Program program = Program::NoProgram;

void setup() {
    Serial.begin(9600);
    relayHandler.addSafetyHandler(&safetyHandler);
    userControl.begin();
    lcdHandler.begin();
    viewHandler.bootView();
    delay(1000); // Animation time
    viewHandler.selectActionView();
}

void EcoProgram() {
    if(!safetyHandler.safeModeIsActive()) {
        switch (program_step)
        {
            case 0: {
                time = actionsHandler.fillWater();
                if (time == 0 && actionsHandler.currentAction() == ActiveAction::noAction) {
                    program_step++;
                }
            }
            break;

            case 1:
                time = actionsHandler.addSoap();
                if (time == 0 && actionsHandler.currentAction() == ActiveAction::noAction) {
                    program_step++;
                }
            break;

            case 2:
                time = actionsHandler.wash(1);
                if (time == 0 && actionsHandler.currentAction() == ActiveAction::noAction) {
                    program_step++;
                }
            break;

            case 3:
                time = actionsHandler.emptyWater();
                if (time == 0 && actionsHandler.currentAction() == ActiveAction::noAction) {
                    program_step++;
                }
            break;

            case 4:
                Serial.println("Eco program ready.");
                program_step++;
            break;
        }
    }

    if(printed_test_time != time) {
        Serial.print("time:");
        printed_test_time = time;
        Serial.println(time);
    }
}

void BasicProgram() {
    
}

void SuperProgram() {
    
}

void loop() {
    safetyHandler.safetyLoop();
    userControl.loop();

    if(userControl.userScrollLeft())
    {
        Serial.println("left");
    }
    if(userControl.userScrollRight())
    {
        Serial.println("right");
    }
    if(userControl.userPress())
    {
        Serial.println("press");
    }

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