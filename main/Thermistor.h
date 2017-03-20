#ifndef THERMISTOR_H
#define THERMISTOR_H
#include "Sensor.h"

class Thermistor : public Sensor
{
public:
    Thermistor(int pin);
    float read() override;
};

#endif //THERMISTOR_H
