#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

ESP8266WebServer server(80);

int total_time = 0, action_time = 0, action = 0;
String special = "";


// Wlan settings
String ssid = "";
String pass = "";
IPAddress local_IP;
IPAddress gateway;
IPAddress subnet;
bool useStaticIP = false;

void handleRoot() {
  String json = "{";
  json += "\"action\":" + String(action) + ",";
  json += "\"time\":" + String(action_time) + ",";
  json += "\"special\":\"" + special + "\",";
  json += "\"totalTime\":" + String(total_time);
  json += "}";
  
  server.send(200, "application/json", json);
}

// EEPROM-tallennus
void saveWiFiSettings() {
  EEPROM.begin(512);
  int addr = 0;
  EEPROM.write(addr++, ssid.length());
  for (int i = 0; i < ssid.length(); i++) EEPROM.write(addr++, ssid[i]);
  EEPROM.write(addr++, pass.length());
  for (int i = 0; i < pass.length(); i++) EEPROM.write(addr++, pass[i]);
  EEPROM.write(addr++, useStaticIP ? 1 : 0);
  if (useStaticIP) {
    for (int i = 0; i < 4; i++) EEPROM.write(addr++, local_IP[i]);
    for (int i = 0; i < 4; i++) EEPROM.write(addr++, gateway[i]);
    for (int i = 0; i < 4; i++) EEPROM.write(addr++, subnet[i]);
  }
  EEPROM.commit();
}

void loadWiFiSettings() {
  EEPROM.begin(512);
  int addr = 0;
  int len = EEPROM.read(addr++);
  ssid = "";
  for (int i = 0; i < len; i++) ssid += char(EEPROM.read(addr++));
  len = EEPROM.read(addr++);
  pass = "";
  for (int i = 0; i < len; i++) pass += char(EEPROM.read(addr++));
  useStaticIP = EEPROM.read(addr++) == 1;
  if (useStaticIP) {
    byte ip[4], gw[4], sn[4];
    for (int i = 0; i < 4; i++) ip[i] = EEPROM.read(addr++);
    for (int i = 0; i < 4; i++) gw[i] = EEPROM.read(addr++);
    for (int i = 0; i < 4; i++) sn[i] = EEPROM.read(addr++);
    local_IP = IPAddress(ip);
    gateway  = IPAddress(gw);
    subnet   = IPAddress(sn);
  }
}

void connectWiFi() {
  if (ssid.length() == 0) {
    Serial.println("No WiFi credentials saved");
    return;
  }
  if (useStaticIP) {
    WiFi.config(local_IP, gateway, subnet);
  }
  WiFi.begin(ssid.c_str(), pass.c_str());
  Serial.println("Connecting to WiFi");
  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 30) {
    delay(500);
    //Serial.print(".");
    retries++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(" CONNECTED ");
    Serial.println(WiFi.localIP().toString());
  } else {
    Serial.println(" DISCONNECTED");
  }
}

void parseCommand(String line) {
  line.trim();

  // Wlan
  if (line.startsWith("SET WIFI=")) {
    int comma = line.indexOf(',', 9);
    if (comma != -1) {
      ssid = line.substring(9, comma);
      pass = line.substring(comma + 1);
      saveWiFiSettings();
      connectWiFi();
      Serial.println("OK WIFI");
    }
  }
  // STATIC IP
  else if (line.startsWith("SET IP=")) {
    int p1 = line.indexOf(',', 7);
    int p2 = line.indexOf(',', p1 + 1);
    if (p1 != -1 && p2 != -1) {
      local_IP.fromString(line.substring(7, p1));
      gateway.fromString(line.substring(p1 + 1, p2));
      subnet.fromString(line.substring(p2 + 1));
      useStaticIP = true;
      saveWiFiSettings();
      Serial.println("OK IP");
    }
  }
  // VALUES
  else if (line.startsWith("SET ACTION=")) {
    action = line.substring(11).toInt();
    Serial.println("OK ACTION");
  }
  else if (line.startsWith("SET TIME=")) {
    action_time = line.substring(9).toInt();
    Serial.println("OK TIME");
  }
  else if (line.startsWith("SET TOTAL=")) {
    total_time = line.substring(10).toInt();
    Serial.println("OK TOTAL");
  }
  else if (line.startsWith("SET SPECIAL=")) {
    special = line.substring(12);
    Serial.println("OK SPECIAL");
  }
  // STATUS
  else if (line == "STATUS") {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("CONNECTED " + WiFi.localIP().toString());
    } else {
      Serial.println("DISCONNECTED");
    }
  }
  else {
    Serial.println("ERROR");
  }
}

void setup() {
  Serial.begin(115200);

  loadWiFiSettings();
  connectWiFi();

  server.on("/", handleRoot);
  server.begin();

  Serial.println("serverready");
}

void loop() {
  server.handleClient();

  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    parseCommand(cmd);
  }
}
