#include "UserControl.h"

volatile int UserControl::lastEncoded = 0, UserControl::pos = 0, UserControl::lastPos = 0;

void UserControl::begin() {
  last_action = millis();
  last_press = millis();
  pinMode(ENCODER_RIGHT_PIN, INPUT);
  pinMode(ENCODER_LEFT_PIN, INPUT);
  digitalWrite(ENCODER_RIGHT_PIN, HIGH);
  digitalWrite(ENCODER_LEFT_PIN, HIGH);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT_PIN), UserControl::UpdateEncoderScroll, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT_PIN), UserControl::UpdateEncoderScroll, CHANGE);
}

void UserControl::UpdateEncoderScroll()
{
  int MSB = digitalRead(PIN_EncoderRight); 
  int LSB = digitalRead(PIN_EncoderLeft);

  int encoded = (MSB << 1) | LSB; 
  int sum = (lastEncoded << 2) | encoded; 

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) pos++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) pos--;

  lastEncoded = encoded; 
}

void UserControl::loop() {
  buttonValue = analogRead(PIN_EncoderPress);
  Serial.println(buttonValue);
}

bool UserControl::userScrollRight() {
  if (pos < lastPos-3) {
    lastPos = pos;
    if(last_action+100<millis()) {
      last_action=millis(); 
      return true;
    }
  }
  return false;
}

bool UserControl::userScrollLeft() {
  if (pos > lastPos+3) {
    lastPos = pos;
    if(last_action+100<millis()) {
      last_action=millis(); 
      return true;
    }
  }
  return false;
}

bool UserControl::userPress() {
  if(buttonValue > 1000 && last_press + 1000 < millis()) {
    last_press=millis(); 
    return true;
  }
  return false;
}