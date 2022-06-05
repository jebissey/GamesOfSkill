#ifndef PONG_H
#define PONG_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


static unsigned long moveTheBallTime;

#include "MatriceLeds.h"
static MatriceLeds matriceLeds;

#include "Gy521.h"
#include "LedsSquare.h"

class Pong
{
  private:
  static const int timeBetweenBallMove = 100;
  static Gy_521 gy521;
  int  GyAccTemp[gy521.numData];
  float PitchRoll[3];
  LedsSquare ledsSquare = LedsSquare(matriceLeds, RowCol(2, 2));
  
  public:
  void Setup(){
    gy521.Setup();
    ledsSquare.MoveAbsolute(RowCol(3, 3));
  }
  
  void MoveTheBall(){
    if(time.IsOver(timeBetweenBallMove, &moveTheBallTime)){
      gy521.ReadGY521(GyAccTemp);
      gy521.ComputeAngle(GyAccTemp,PitchRoll);
      int ballRowIncrement = round(map(PitchRoll[1], -90, +90, -10, +10) / 3.0);
      int ballColIncrement = round(map(PitchRoll[2], -90, +90, +10, -10) / 3.0);
      ledsSquare.MoveRelative(RowCol(ballRowIncrement, ballColIncrement));
    }
  }

  float GetTemperature(){
    return gy521.temperature;
  }
};
#endif
