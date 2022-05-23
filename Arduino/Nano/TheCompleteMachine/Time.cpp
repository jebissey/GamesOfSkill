#include "Time.h"


bool Time::NewDeciSecond(unsigned long *deciSecond, unsigned long lastDeciSecond)
{
  *deciSecond = millis() / 100;
  if(*deciSecond != lastDeciSecond) return true;
  return false;
}

bool Time::NewSecond(unsigned long *second, unsigned long lastSecond)
{  
  *second = millis() / 1000; 
  if(*second != lastSecond) return true;
  return false;
}

bool Time::NewMinute(unsigned long *minute, unsigned long lastMinute)
{
  *minute = millis() / (1000 * 60);
  if(*minute != lastMinute) return true;
  return false;
}


bool Time::NewHour(unsigned long *hour, unsigned long lastHour)
{
  *hour = millis() / (1000 * 60 * 60);
  if(*hour != lastHour) return true;
  return false;
}
