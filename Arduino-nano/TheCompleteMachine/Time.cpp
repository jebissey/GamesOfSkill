#include "Time.h"

bool Time::IsOver(int delayForInMilisecond, unsigned long *timerFor)
{
  if((millis() - *timerFor) <= delayForInMilisecond) return false;
  *timerFor = millis();
  return true; 
}

void Time::Reset(unsigned long *timerFor)
{
  *timerFor = millis();
}
