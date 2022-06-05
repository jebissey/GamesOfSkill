#ifndef PONG_H
#define PONG_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#include "Time.h"
static unsigned long aTime;
static Time time;


#include "MatriceLeds.h"
static MatriceLeds matriceLeds;


#include "LedsSquare.h"
RowCol squareSize = RowCol(2, 2);
LedsSquare ledsSquare = LedsSquare(matriceLeds, squareSize);


#include "Gy521.h"
static Gy_521 gy521;
static int  GyAccTemp[gy521.numData];
static float PitchRoll[3];


class Pong
{
  public:
  void Setup(){
    gy521.Setup();
    ledsSquare.MoveAbsolute(RowCol(3, 3));
  }
  
  
  void MoveTheBall(){
    if(time.IsOver(100, &aTime)){
      gy521.ReadGY521(GyAccTemp);
      gy521.ComputeAngle(GyAccTemp,PitchRoll);
      int ballRowIncrement = round(map(PitchRoll[1], -90, +90, -10, +10) / 3.0);
      int ballColIncrement = round(map(PitchRoll[2], -90, +90, +10, -10) / 3.0);
      ledsSquare.MoveRelative(RowCol(ballRowIncrement, ballColIncrement));
    }
  }
};
#endif
