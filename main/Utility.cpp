#include "Utility.h"
#include <Arduino.h>
#include <vector>
#include <string>

void FlushSerialBuffer()
{
    while (Serial.available() > 0) 
        Serial.read();

    // Output message
    if (Serial.available() == 0)
        Serial.println("Serial is flushed");
    else
        Serial.println("Error: unable to flush serial buffer");
}

void WaitForInput()
{
    while (Serial.available() <= 0)
        delay(1);
}

std::vector<String> SplitString(String str)
{
  std::vector<String> result;
  // If str is empty, return
  if (str.length() == 0)
      return result;

  std::string cppstr(str.c_str());
  cppstr = cppstr + ' '; // Append a space on the back
  int pos = -1, pos_old = -1; // Assuming that there is a space in front of the first character in the string
  // Append all stuff between spaces into the vector
  while ((pos = cppstr.find(' ', pos + 1)) != std::string::npos)
  {
    result.push_back(String(cppstr.substr(pos_old + 1, pos - pos_old - 1).c_str()));
    pos_old = pos;
  }
  return result;
}

