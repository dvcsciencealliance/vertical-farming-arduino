#include "config.h"
#include "Sensor.h"

#if USE_THERMISTOR
#include "Thermistor.h"
#endif //USE_THERMISTOR

#if USE_PH_SENSOR
#include "pH_Sensor.h"
#endif //USE_PH_SENSOR

// Global variables
Sensor** sensors; // An unknown size of array of pointers to sensor
int SensorCnt; // Total amount of sensors

void setup()
{
    // Count total amount of sensors
    SensorCnt = 0;
    if (USE_THERMISTOR)
        ++SensorCnt;
    if (USE_PH_SENSOR)
        ++SensorCnt;
        
    // Allocate memory for sensors
    sensors = new Sensor*[SensorCnt];  // Since memory will be ereased once Arduino is power off, let's not worry about memory leak
    // Init sensors
    int cnt = SensorCnt;
    #if (USE_THERMISTOR)
        sensors[--cnt] = new Thermistor(PIN_THERMISTOR);
    #endif
    #if (USE_PH_SENSOR)
        sensors[--cnt] = new pH_Sensor(PIN_PH_SENSOR);
    #endif

    // Open serial connection
    Serial.begin(BAUDRATE);
}

void loop() 
{
    for (int i = 0; i < SensorCnt; ++i)
    {
        // Just for demo
        String output;
        output = sensors[i]->name() + ": " + sensors[i]->read(); 
        Serial.println(output); // println will print newline automatically
    }
    Serial.print('\n');
    delay(1000);
}

