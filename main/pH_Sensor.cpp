#include "pH_Sensor.h"

pH_Sensor::pH_Sensor(int pin, String name)
    :
    Sensor(pin, SensorType::pH, name)
{
}

float pH_Sensor::read()
{
    float count = analogRead(m_pin);
    float slope = -3.838;
    float intercept = 13.720;
    float voltage = count / 1023 * 5.0;
    float ph = intercept + voltage * slope;
    return ph;
}

