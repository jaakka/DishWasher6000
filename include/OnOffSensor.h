#ifndef ONOFFSENSOR_H
#define ONOFFSENSOR_H

class OnOffSensor {
public:
    OnOffSensor(int pin);
    bool isOn() const;

private:
    int sensor_pin;
};

#endif