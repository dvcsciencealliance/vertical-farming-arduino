#include "config.h"

#if USE_THERMISTOR // Skip compilation if this sensor is not used

#include "Thermistor.h"

Thermistor::Thermistor(int pin)
    : Sensor(pin, SensorType::Thermistor)
{
}

float Thermistor::read()
{
    /*  Inputs ADC count from thermistor and outputs temperature in Celsius
        requires: include <math.h>,
        Vernier Stainless Steel Temperature Probe TMP-BTA, Vernier Surface Temperature Probe STS-BTA
        This version utilizes the Steinhart-Hart Thermistor Equation:
        Temperature in Kelvin = 1 / {A + B[ln(R)] + C[ln(R)]^3}
        for the themistor in the Vernier TMP-BTA probe:
        A = 0.00102119 , B = 0.000222468 and C = 1.33342E-7
        Using these values should get agreement within 1 degree C to the same probe used with one of the Vernier interfaces.

        Schematic:
        [Ground] -- [thermistor] -------- | -- [15,000 ohm resistor] -- [Vcc (5v)]
                                       |
                                  Analog Pin 0
        For the circuit above:
        Resistance = ( Count*RawADC /(1024-Count))
    */
    float count = analogRead(m_pin);
    float resistor = 15000;
    long resistance = (resistor * count / (1024 - count));
    float logResistance = log(resistance);
    float tempInKelvin = 1 / (0.00102119 + (0.000222468 * logResistance) + (0.000000133342 * pow(logResistance, 3)));
    float tempInCelsius = tempInKelvin - 273.15;
    return tempInCelsius;
}


#endif //USE_THERMISTOR
