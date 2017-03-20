#include "config.h"

#if USE_PH_SENSOR // Skip compilation if this sensor is not used
#include "pH_Sensor.h"

pH_Sensor::pH_Sensor(int pin)
    :
    Sensor(pin, SensorType::pH)
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

#endif //USE_PH_SENSOR
