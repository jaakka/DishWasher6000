#include "WlanHandler.h"

WlanHandler::WlanHandler() : wlanSerial_(WLAN_RX, WLAN_TX) 
{}

void WlanHandler::begin() {
    wlanSerial_.begin(9600);
    sendCommand("AT+RST"); // Resetoi ESP
    delay(2000);
    connectWifi("", "");
}

void WlanHandler::sendCommand(const String& cmd) {
    wlanSerial_.println(cmd);
}

String WlanHandler::readResponse() {
    String response = "";
    while (wlanSerial_.available()) {
        response += wlanSerial_.readStringUntil('\n');
    }
    return response;
}

void WlanHandler::connectWifi(const String& ssid, const String& password) {
    sendCommand("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
}

bool WlanHandler::isConnected() {
    sendCommand("AT+CWJAP?");
    String resp = readResponse();
    bool test = resp.indexOf("No AP") == -1;
    Serial.print("wlantest:");
    Serial.println(resp);
    return test;
}