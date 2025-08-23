#ifndef RELAY_H
#define RELAY_H

class Relay {
public:
    Relay(int pin);
    void on();
    void off();
    bool isActive() const;

private:
    int pin_;
};

#endif