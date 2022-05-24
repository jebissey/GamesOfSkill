#ifndef BUILTINLED_H
#define BUILTINLED_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Time.h"

class BuiltInLed
{
  private:
  Time time;
  unsigned long timeInMs;
  boolean ledStatus;
  
  public:
  BuiltInLed();
  void Display(int halfTimeDuration);
};
#endif
