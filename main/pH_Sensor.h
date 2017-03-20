#ifndef PH_SENSOR_H
#define PH_SENSOR_H
#include "Sensor.h"

class pH_Sensor : public Sensor
{
public:
    pH_Sensor(int pin);
    float read() override;
};

#endif //PH_SENSOR_H
