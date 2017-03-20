#ifndef SENSOR_H
#define SENSOR_H
#include <Arduino.h>

enum class SensorType
{
    DefaultSensor,
    Thermistor,
    pH
};

class Sensor
{
public:
    Sensor(int pin, SensorType type);
    virtual float read();
    virtual String name();

protected:
    int m_pin;
    SensorType m_type;
    String m_name;
};

String GetSensorNameByType(SensorType type);
#endif //SENSOR_H
