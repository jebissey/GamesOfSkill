#ifndef TIME_H
#define TIME_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class Time
{
  public:
  bool Delay(unsigned long *time, unsigned long lastTime, int delayInMilisecond);
  void Reset(unsigned long *time);
};
#endif
