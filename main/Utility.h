#pragma once

#ifndef UTILITY_H
#define UTILITY_H
#include <ArduinoSTL.h>

void FlushSerialBuffer();
void WaitForInput();
std::vector<String> SplitString(String str);

#endif // UTILITY_H
