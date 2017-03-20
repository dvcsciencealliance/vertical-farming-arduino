#include "Sensor.h"

Sensor::Sensor(int pin, SensorType type)
    :
    m_pin(pin),
    m_type(type),
    m_name(GetSensorNameByType(type))
    {
    }

float Sensor::read()
{
    return (float)analogRead(m_pin) * 0.049; // Return the voltage in V
}

String Sensor::name()
{
    return m_name;
}

String GetSensorNameByType(SensorType type)
{
    switch (type)
    {
    case SensorType::DefaultSensor:
        return "Sensor";
        break;

    case SensorType::Thermistor:
        return "Temperature";
        break;

    case SensorType::pH:
        return "pH";
        break;

    default:
        return "Sensor";
        break;

    }
}

