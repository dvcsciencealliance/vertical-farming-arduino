#ifndef CONFIG_H
#define CONFIG_H

#define BAUDRATE              9600

#define USE_THERMISTOR        1
#if  USE_THERMISTOR
#define PIN_THERMISTOR        0
#endif //USE_THERMISTOR

#define USE_PH_SENSOR         0
#if  USE_PH_SENSOR
#define PIN_PH_SENSOR         0
#endif //USE_THERMISTOR

#endif //CONFIG_H
