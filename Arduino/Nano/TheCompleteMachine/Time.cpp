#include "Time.h"


bool Time::NewDeciSecond(unsigned long *time, unsigned long lastTime)
{
  *time = millis() / 100;
  if(*time != lastTime) return true;
  return false;
}

bool Time::NewSecond(unsigned long *time, unsigned long lastTime)
{  
  *time = millis() / 1000; 
  if(*time != lastTime) return true;
  return false;
}

bool Time::NewTenSeconds(unsigned long *time, unsigned long lastTime)
{  
  *time = millis() / 10000; 
  if(*time != lastTime) return true;
  return false;
}

bool Time::NewMinute(unsigned long *time, unsigned long lastTime)
{
  *time = millis() / (1000 * 60);
  if(*time != lastTime + 1000 * 60) return true;
  return false;
}

bool Time::NewHour(unsigned long *hour, unsigned long lastHour)
{
  *hour = millis() / (1000 * 60 * 60);
  if(*hour != lastHour) return true;
  return false;
}
