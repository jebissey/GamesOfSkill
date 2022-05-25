#include "Time.h"

bool Time::Delay(unsigned long *time, unsigned long lastTime, int delayInMilisecond)
{
  if((millis() - *time) <= delayInMilisecond) return false;
  *time = millis();
  return true; 
}

void Time::Reset(unsigned long *time)
{
  *time = millis();
}
