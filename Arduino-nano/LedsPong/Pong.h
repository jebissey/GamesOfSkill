#ifndef PONG_H
#define PONG_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Fsm.h>

static unsigned long timerForMoveTheBall;

#include "MatriceLeds.h"
static MatriceLeds matriceLeds;

#include "Gy521.h"
#include "LedsSquare.h"



class Pong : public Fsm
{
  private:
  static const int timeBetweenBallMove = 100;
  const RowCol ballSize = RowCol(2, 2);
  const RowCol ballCoordonateAtStartUp = RowCol(3, 3);
  static Gy_521 gy521;
  float PitchRoll[3];
  LedsSquare ledsSquare = LedsSquare(matriceLeds, ballSize);

  static void CreateWall(){
    enum WallPosition{noWall, north, est, sud, west};
    static int wallPosition = noWall;

    while(1==1){
      int newWallPosition = random(north, west);
      if(wallPosition != newWallPosition){
        wallPosition = newWallPosition;
        break;
      }
    }
    switch(wallPosition){
      case north:
        matriceLeds.SetRow(7, B11111111);
        break;
      case est:
        matriceLeds.SetColumn(0, B11111111);
        break;
      case sud:
        matriceLeds.SetRow(0, B11111111);
        break;
      case west:
        matriceLeds.SetColumn(7, B11111111);
        break;
    }
  }
  
  static void MoveBall(){
    
  }
  
  static void BlinkWall(){
    
  }
  
  static void EraseWall(){
    
  }
  
  static void EraseBall(){
    
  }
  
  static void WinPoint(){
    
  }
    
  static void StartTimerWallBeforeBlink(){
    
  }
  
  enum Event { ballMovedOutside, ballHitedWall, timeoutWallBeforeBlinkIsOver, timeoutWallBlinkking, boardShaked, wallExist};
  Event GetEvent()
  {
    
  }
  
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
  
  void Run(){
    run_machine();
    trigger(GetEvent());
  }

  State createWall = State(CreateWall, NULL, StartTimerWallBeforeBlink);
  State moveBall =   State(NULL, MoveBall, NULL);
  State eraseBall =  State(EraseBall, NULL, NULL);
  State blinkWall =  State(NULL, BlinkWall, NULL);
  State eraseWall =  State(EraseWall, NULL, NULL);
  State winPoint =   State(WinPoint, NULL, NULL);

  Pong() : Fsm(&createWall){
    this->add_transition(&createWall,  &moveBall, wallExist, NULL);
    this->add_transition(&createWall,  &blinkWall, timeoutWallBeforeBlinkIsOver, NULL);
  }
  
};

#endif
