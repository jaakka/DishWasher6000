#include "WlanHandler.h"

WlanHandler::WlanHandler() : wlanSerial_(WLAN_RX, WLAN_TX) 
{}

void WlanHandler::setWifi(const String& ssid, const String& password) {
    wlanSerial_.println("SET WIFI=" + ssid + "," + password);
}

void WlanHandler::setAction(int action) {
    wlanSerial_.println("SET ACTION=" + String(action));
}

void WlanHandler::setTime(int time) {
    wlanSerial_.println("SET TIME=" + String(time));
}

void WlanHandler::setTotalTime(int total) {
    wlanSerial_.println("SET TOTAL=" + String(total));
}

void WlanHandler::setSpecial(const String& special) {
    wlanSerial_.println("SET SPECIAL=" + special);
}

bool WlanHandler::isConnected() {
    wlanSerial_.println("STATUS");
    delay(100);
    String resp = "";
    while (wlanSerial_.available()) {
        resp += wlanSerial_.readStringUntil('\n');
    }
    Serial.println(resp);
    return resp.startsWith("CONNECTED");
}

void WlanHandler::startCommunication() {
    wlanSerial_.begin(115200);
    delay(10);
}

void WlanHandler::stopCommunication() {
    wlanSerial_.end();
    delay(10); 
}

String WlanHandler::getIp() {
    wlanSerial_.println("STATUS");
    delay(100);
    String resp = "";
    while (wlanSerial_.available()) {
        resp += wlanSerial_.readStringUntil('\n');
    }
    int idx = resp.indexOf("CONNECTED ");
    if (idx != -1) {
        String ip = resp.substring(idx + 10 + 7); // 10 = strlen("CONNECTED ")
        ip.trim();
        return "x.x"+String(ip);
    }
    return "";
}