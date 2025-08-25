#ifndef USERCONTROL_H
#define USERCONTROL_H

#include <HardwareSerial.h>
#include <Arduino.h>
#include "pins.h"

#define PIN_EncoderLeft 2
#define PIN_EncoderRight 3
#define PIN_EncoderPress A6

class UserControl {
  public:
    void begin();
    void loop();
    bool userScrollRight();
    bool userScrollLeft();
    bool userPress();
    static void UpdateEncoderScroll();
  private:  
    unsigned long last_action;
    unsigned long last_press;
    static volatile int lastEncoded;
    static volatile int pos;
    static volatile int lastPos;
    int buttonValue;
};

#endif