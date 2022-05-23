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
  bool NewDeciSecond(unsigned long *deciSecond, unsigned long lastDeciSecond);
  bool NewSecond(unsigned long *second, unsigned long lastSecond);
  bool NewMinute(unsigned long *minute, unsigned long lastMinute);
  bool NewHour(unsigned long *hour, unsigned long lastHour);

  private:
  
};
#endif
