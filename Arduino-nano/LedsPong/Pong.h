#ifndef PONG_H
#define PONG_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


static unsigned long timerForMoveTheBall;

#include "MatriceLeds.h"
static MatriceLeds matriceLeds;

#include "Gy521.h"
#include "LedsSquare.h"

class Pong
{
  private:
  static const int timeBetweenBallMove = 100;
  const RowCol ballSize = RowCol(2, 2);
  const RowCol ballCoordonateAtStartUp = RowCol(3, 3);
  static Gy_521 gy521;
  float PitchRoll[3];
  LedsSquare ledsSquare = LedsSquare(matriceLeds, ballSize);
  
  public:
  void Setup(){
    gy521.Setup();
    ledsSquare.MoveAbsolute(ballCoordonateAtStartUp);
  }
  
  void MoveTheBall(){
    if(time.IsOver(timeBetweenBallMove, &timerForMoveTheBall)){
      gy521.Read(PitchRoll);
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
