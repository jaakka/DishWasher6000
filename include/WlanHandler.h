#ifndef WLANHANDLER_H
#define WLANHANDLER_H

#include "pins.h"
#include <SoftwareSerial.h>
#include <Arduino.h>

class WlanHandler 
{
    public:
        WlanHandler();
        void setWifi(const String& ssid, const String& password);
        void setAction(int action);
        void setTime(int time);
        void setTotalTime(int total);
        void setSpecial(const String& special);
        bool isConnected();
        String getIp();
        void startCommunication();
        void stopCommunication();
    private:
        SoftwareSerial wlanSerial_;
};

#endif