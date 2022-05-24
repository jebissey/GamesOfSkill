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
  bool NewDeciSecond(unsigned long *time, unsigned long lastTime);
  bool NewSecond(unsigned long *time, unsigned long lastTime);
  bool NewTenSeconds(unsigned long *time, unsigned long lastTime);
  bool NewMinute(unsigned long *time, unsigned long lastTime);
  bool NewHour(unsigned long *time, unsigned long lastTime);

  private:
  
};
#endif
