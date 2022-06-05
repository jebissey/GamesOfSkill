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
  
  bool IsOver(int delayForInMilisecond, unsigned long *timerFor){
    if((millis() - *timerFor) <= delayForInMilisecond) return false;
    *timerFor = millis();
    return true; 
  }
  
  void Reset(unsigned long *timerFor){
    *timerFor = millis();
  }
};
#endif
