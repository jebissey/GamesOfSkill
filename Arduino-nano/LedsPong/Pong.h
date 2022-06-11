#ifndef PONG_H
#define PONG_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Fsm.h>

static unsigned long timerForMoveTheBall;
static unsigned long timerForWallStartBlink;

#include "MatriceLeds.h"
static MatriceLeds matriceLeds;

#include "Gy521.h"
#include "LedsSquare.h"


static const RowCol ballSize = RowCol(2, 2);
static LedsSquare ledsSquare = LedsSquare(matriceLeds, ballSize);


class Pong : public Fsm {
private:
  const RowCol ballCoordonateAtStartUp = RowCol(3, 3);
  static Gy_521 gy521;
  static float boardTilts[3];


#include "Pong.TheWall.h"
#include "Pong.TheBall.h"
#include "Pong.Events.h"
  Events events;
  
  static void WinPoint(){
    
  }

   
  static void StartTimerWallBeforeBlink(){
    time.Reset(&timerForWallStartBlink);
  }

  
public: 
  void Setup(){
    gy521.Setup();
    ledsSquare.MoveAbsolute(ballCoordonateAtStartUp);
  }

  float GetTemperature(){
    return gy521.temperature;
  }
  
  void Run(){
    run_machine();
    trigger(events.GetEvent());
  }


  State createWall =  State(TheWall::Create,  NULL, StartTimerWallBeforeBlink);
  State displayWall = State(TheWall::Display, NULL, StartTimerWallBeforeBlink);
  State displayBall = State(TheBall::Move,    NULL, StartTimerWallBeforeBlink);
  State playOver =    State(TheBall::Move,    NULL, StartTimerWallBeforeBlink);
  State gameOver =    State(TheBall::Move,    NULL, StartTimerWallBeforeBlink);

  Pong() : Fsm(&createWall){
    this->add_transition(&createWall,  &displayBall, Events::wallExist,        NULL);
    this->add_transition(&createWall,  &displayWall, Events::wallExist,        NULL);
    this->add_transition(&displayBall, &playOver,    Events::winnedPoint,      NULL);
    this->add_transition(&displayWall, &playOver,    Events::ballMovedOutside, NULL);
    this->add_transition(&playOver,    &createWall,  Events::winnedPoint,      NULL);
    this->add_transition(&playOver,    &gameOver,    Events::gameOver,         NULL);
    
    Events::SetCheckEvents(Events::CheckEventsDuringGame);
  } 
};


float Pong::boardTilts[3];
Pong::Events::Event (* Pong::Events::checkEvents)();
int Pong::TheWall::wallPosition;

#endif
