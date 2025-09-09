#include <Arduino.h>
#include "SafetyHandler.h"
#include "RelayHandler.h"
#include "SensorHandler.h"
#include "ActionsHandler.h"
#include "UserControl.h"
#include "LcdHandler.h"
#include "ViewHandler.h"
#include "WlanHandler.h"

RelayHandler relayHandler;
SensorHandler sensorHandler;
SafetyHandler safetyHandler(relayHandler, sensorHandler);
ActionsHandler actionsHandler(sensorHandler, relayHandler);
UserControl userControl;
LcdHandler lcdHandler;
ViewHandler viewHandler(lcdHandler);
WlanHandler wlanHandler;

enum class Program {
    NoProgram,
    Eco,
    Normal,
    Super
};


int time = 1;
int program_step = 0;
int action = 0;
int printed_time = 0;
int printed_action = 0;
bool lcd_updated = false;

int menu = 0;
Program program = Program::NoProgram;

void setup() {
    Serial.begin(115200);
    relayHandler.addSafetyHandler(&safetyHandler);
    userControl.begin();
    lcdHandler.begin();
    viewHandler.bootView();
    delay(1000); // Intro time
    viewHandler.selectActionView();
}

void NoProgram() {
    if(userControl.userScrollRight()) {
        lcd_updated = false;
        if(menu<5) {
            menu++;
        } else {
            menu = 1;
        }
    } else if(userControl.userScrollLeft()) {
        lcd_updated = false;
        if(menu>1) {
            menu--;
        } else {
            menu = 5;
        }
    }

    if(userControl.userPress()) {
        switch (menu)
        {
            case 1:
                program = Program::Eco;
            break;

            case 2:
                program = Program::Normal;
            break;

            case 3:
                program = Program::Super;
            break;

            case 4: 
                relayHandler.powerOff();
            break;
        }
    }

    if(!lcd_updated){
        switch (menu)
        {
            case 1:
                viewHandler.ecoWash();
            break;

            case 2:
                viewHandler.normalWash();
            break;

            case 3:
                viewHandler.superWash();
            break;

            case 4: 
                viewHandler.mainPower();
            break;

            case 5:
                lcdHandler.stopCommunication();
                wlanHandler.startCommunication();

                String ip = wlanHandler.getIp();
                
                wlanHandler.stopCommunication();
                lcdHandler.startCommunication();
                if(ip == ""){
                    viewHandler.wlanState();
                }else{
                    viewHandler.wlanState(ip);
                }
            break;
        }
        lcd_updated = true;
    }
}


void ProgramInformationUpdate() {

    if(printed_time != time) {

        if(actionsHandler.currentAction() != ActiveAction::noAction){
            lcdHandler.DrawText(TextPosition::CENTER_BOTTOM,String(time)+"s");
        }

        lcdHandler.stopCommunication();
        wlanHandler.startCommunication();

        wlanHandler.setTime(time);

        wlanHandler.stopCommunication();
        lcdHandler.startCommunication();

        printed_time = time;
    }

    if(printed_action != action) {

        if(actionsHandler.currentAction() == ActiveAction::addSoap)
        {
            lcdHandler.DrawLargeIcon(LargeIcon::SOAP);
            lcdHandler.DrawText(TextPosition::CENTER_TOP,"Pesuaine");
        }
        else if(actionsHandler.currentAction() == ActiveAction::checkWater)
        {
            lcdHandler.DrawLargeIcon(LargeIcon::TIME);
            lcdHandler.DrawText(TextPosition::CENTER_TOP,"60/95");
        }
        else if(actionsHandler.currentAction() == ActiveAction::emptyWater)
        {
            lcdHandler.DrawLargeIcon(LargeIcon::STORM);
            lcdHandler.DrawText(TextPosition::CENTER_TOP,"Poisto");
        }
        else if(actionsHandler.currentAction() == ActiveAction::fillWater)
        {
            lcdHandler.DrawLargeIcon(LargeIcon::WATER);
            lcdHandler.DrawText(TextPosition::CENTER_TOP,"Otto");
        }
        else if(actionsHandler.currentAction()  == ActiveAction::heat)
        {
            lcdHandler.DrawLargeIcon(LargeIcon::FIRE);
            lcdHandler.DrawText(TextPosition::CENTER_TOP,"23/64");
        }
        else if(actionsHandler.currentAction() == ActiveAction::wash)
        {
            lcdHandler.DrawLargeIcon(LargeIcon::RESTART);
            lcdHandler.DrawText(TextPosition::CENTER_TOP,"Pesu");
        }
        else if(actionsHandler.currentAction() == ActiveAction::noAction)
        {
            lcdHandler.DrawLargeIcon(LargeIcon::HOME);
            lcdHandler.DrawText(TextPosition::CENTER_TOP,"Valmis");
            lcdHandler.DrawText(TextPosition::CENTER_BOTTOM,"32m 23s");
        }

        lcdHandler.stopCommunication();
        wlanHandler.startCommunication();

        wlanHandler.setAction(static_cast<int>(actionsHandler.currentAction()));

        wlanHandler.stopCommunication();
        lcdHandler.startCommunication();

        printed_action = action;
    }
}


void EcoProgram() {
    if(!safetyHandler.safeModeIsActive()) {
        switch (program_step)
        {
            case 0: {
                time = actionsHandler.fillWater();
                action = 1;
                if (time == 0 && actionsHandler.currentAction() == ActiveAction::noAction) {
                    program_step++;
                }
            }
            break;

            case 1:
                time = actionsHandler.addSoap();
                action = 2;
                if (time == 0 && actionsHandler.currentAction() == ActiveAction::noAction) {
                    program_step++;
                }
            break;

            case 2:
                time = actionsHandler.heatWarm();
                action = 2;
                if (time == 0 && actionsHandler.currentAction() == ActiveAction::noAction) {
                    program_step++;
                }
            break;

            case 3:
                time = actionsHandler.wash(1);
                action = 4;
                if (time == 0 && actionsHandler.currentAction() == ActiveAction::noAction) {
                    program_step++;
                }
            break;

            case 4:
                time = actionsHandler.emptyWater();
                action = 5;
                if (time == 0 && actionsHandler.currentAction() == ActiveAction::noAction) {
                    program_step++;
                }
            break;

            case 5:
                action = 6;
                Serial.println("Eco program ready.");
                program_step++;
            break;
        }
    }
    ProgramInformationUpdate();
}

void BasicProgram() {
    
}

void SuperProgram() {
    
}

void loop() {
    safetyHandler.safetyLoop();
    userControl.loop();

    switch (program)
    {
        case Program::NoProgram:
            NoProgram();
        break;

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