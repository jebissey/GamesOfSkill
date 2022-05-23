#ifndef BUILTINLED_H
#define BUILTINLED_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class BuiltInLed
{
  public:
  BuiltInLed();
  void Display(int halfTimeDuration);
};
#endif
