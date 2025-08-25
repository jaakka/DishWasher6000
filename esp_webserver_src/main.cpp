#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Arduino.h>

ESP8266WebServer server(80);

void handleRoot() {
  String json = "{";
  json += "\"action\":\"" + String(1) + "\",";
  json += "\"time\":23,";
  json += "\"special\":12,";
  json += "\"totalTime\":332";
  json += "}";
  
  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(9600);
  WiFi.begin("", "");
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.println("serverready");
  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
  if (Serial.available()) {
    String lcdText = Serial.readStringUntil('\n');
  }
}