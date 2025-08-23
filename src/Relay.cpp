#include "Relay.h"
#include <Arduino.h>

Relay::Relay(int pin) : relay_pin(pin) {
    pinMode(relay_pin, OUTPUT); 
    digitalWrite(relay_pin, LOW);
}

void Relay::on() {
    digitalWrite(relay_pin, HIGH);
}

void Relay::off() {
    digitalWrite(relay_pin, LOW);
}

bool Relay::isActive() const {
    return digitalRead(relay_pin) == HIGH;
}