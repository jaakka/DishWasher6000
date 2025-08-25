#ifndef WLANHANDLER_H
#define WLANHANDLER_H

#include "pins.h"
#include <SoftwareSerial.h>
#include <Arduino.h>

class WlanHandler 
{
    public:
        WlanHandler();
        void begin();
        bool isConnected();
    private:
        SoftwareSerial wlanSerial_;
        void sendCommand(const String& cmd);
        String readResponse();
        void connectWifi(const String& ssid, const String& password);
};

#endif
