/// Serial communication protocol reference
/// %VARIABLE% indicates that it is a variable
/// Prefix convention:
/// s       String
/// i       int
/// b       bool
/// f       float

#include <ArduinoSTL.h>
#include <vector>
#include "Utility.h"
#include "Sensor.h"
#include "Thermistor.h"
#include "pH_Sensor.h"

using std::vector;

// Constants
const int BaudRate = 9600; // Transfer rate in bits per second 

// Global variables
vector<Sensor*> sensors;

void setup()
{
    // Open serial connection
    Serial.begin(BaudRate);
    FlushSerialBuffer();
    bool init = false;
    while (!init) 
    {
        init = Init();
    }
}

void loop() 
{
    for (auto&& sensor : sensors)
    {
        String output;
        output = sensor->name() + ' ' + sensor->read(); 
        Serial.println(output); // println will print newline automatically
    }
    delay(1000);
}

bool Init()
{
    // Formate:
    // ----------------------------------------------
    // Line Number  |   Arguments                   
    // ----------------------------------------------
    // Line 0       |   INIT %i_N%
    // Line 1~N-1:  |   %i_TYPE% %s_NAME% %i_PIN%

    
    const int NumOfEle_Init = 2; // Number of elements in INIT
    const int NumOfEle_Sens = 3; // Number of elements in each line follows INIT

    WaitForInput();
    String str = Serial.readString();
    vector<String> data = SplitString(str);

    // Error checking
    if (data[0] != "INIT")
    {
        FlushSerialBuffer();
        Serial.println("Unable to initialize device with string:");
        Serial.println(str);
        return false;
    }
    if (data.size() != NumOfEle_Init)
    {
        FlushSerialBuffer();
        String message = "INIT does not have " + String(NumOfEle_Init) + " arguments:";
        Serial.println(message);
        Serial.println(str);
        return false;
    }
    const int N = data[1].toInt();
    for (int i = 0; i < N; ++i)
    {
        WaitForInput();
        vector<String> sensorInfo = SplitString(Serial.readString()); 
        if (sensorInfo.size() != NumOfEle_Sens)
        {
            FlushSerialBuffer();
            String message = "Sensor line " + String(i) + " does not have " + NumOfEle_Sens + " arguments.";
            Serial.println(message);
            return false;
        }

        int pin = sensorInfo[2].toInt();
        SensorType type = (SensorType)(sensorInfo[0].toInt());
        switch(type)
        {
        case SensorType::Thermistor:
            sensors.push_back(new Thermistor(pin, sensorInfo[1]));
            Serial.println("Temperature sensor with name " + sensorInfo[1] + " at pin " + String(pin) + " was added" );
            break;

        case SensorType::pH:
            sensors.push_back(new pH_Sensor(pin, sensorInfo[1]));
            Serial.println("pH sensor with name " + sensorInfo[1] + " at pin " + String(pin) + " was added" );
            break;

        default:
            sensors.push_back(new Sensor(pin, sensorInfo[1]));
            Serial.println("Default sensor with name " + sensorInfo[1] + " at pin " + String(pin) + " was added" );
            break;
        }
    }

    return true;
}




