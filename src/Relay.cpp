#include "Relay.h"
#include <Arduino.h>

Relay::Relay(int pin) : pin_(pin) {
    pinMode(pin_, OUTPUT); 
    digitalWrite(pin_, LOW);
}

void Relay::on() {
    digitalWrite(pin_, HIGH);
}

void Relay::off() {
    digitalWrite(pin_, LOW);
}

bool Relay::isActive() const {
    return digitalRead(pin_) == HIGH;
}