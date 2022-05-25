#ifndef BALL_H
#define BALL_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Catapult.h"
#include "Time.h"


class Ball
{
  private:
  const int switchOffDelay = 20*1000;
  unsigned long aTime;
  Time time;
  
  public:
  Ball();
  void Catch();
  bool Throw(Catapult Catapult, int position);

    
  void Test();
};

#endif
