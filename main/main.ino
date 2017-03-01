#include <math.h>

int led = 13;
String sensorInfo[][2] = {
  { "Thermistor", " degrees C" },
  { "PH", "" },
  { "None", "" },
  { "None", "" },
  { "None", "" },
  { "None", "" }
};
float sensorValues[] = { 0, 0, 0, 0, 0, 0 };
int refreshDelay = 2000;

void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < sizeof(sensorInfo) / sizeof(sensorInfo[0]); i++) {
    String sensorName = sensorInfo[i][0];
    int count = analogRead(i);
    if (sensorName == "Thermistor") {
      sensorValues[i] = thermistor(count);
    } else if (sensorName == "PH") {
      
    }
  }
  printSensorValues();
  delay(refreshDelay);
}

void printSensorValues() {
  String output = "";
  for (int i = 0; i < sizeof(sensorValues) / sizeof(sensorValues[0]); i++) {
    String sensorName = sensorInfo[i][0];
    String sensorUnits = sensorInfo[i][1];
    int sensorValue = sensorValues[i];
    String period = ". ";
    String colon = ": ";
    output += (i + 1) + period + sensorName;
    if (sensorName != "None") {
      output += colon + sensorValue + sensorUnits;
    }
    output += "\n";
  }
  Serial.println(output);
}

float thermistor(int raw) {
 /* Inputs ADC count from thermistor and outputs temperature in Celsius
  * requires: include <math.h>
  * Vernier Stainless Steel Temperature Probe TMP-BTA, Vernier Surface Temperature Probe STS-BTA
  * This version utilizes the Steinhart-Hart Thermistor Equation:
  * Temperature in Kelvin = 1 / {A + B[ln(R)] + C[ln(R)]^3}
  * for the themistor in the Vernier TMP-BTA probe:
  * A = 0.00102119 , B = 0.000222468 and C = 1.33342E-7
  * Using these values should get agreement within 1 degree C to the same probe used with one of the Vernier interfaces.
  * 
  * Schematic:
  * [Ground] -- [thermistor] -------- | -- [15,000 ohm resistor] -- [Vcc (5v)]
  *                                   |
  *                              Analog Pin 0
  * For the circuit above:
  * Resistance = ( Count*RawADC /(1024-Count))
  */
  float resistor = 15000;
  long resistance = (resistor * raw / (1024 - raw));
  float logResistance = log(resistance);
  float tempInKelvin = 1 / (0.00102119 + (0.000222468 * logResistance) + (0.000000133342 * pow(logResistance, 3)));
  float tempInCelsius = tempInKelvin - 273.15;
  return tempInCelsius;
}

