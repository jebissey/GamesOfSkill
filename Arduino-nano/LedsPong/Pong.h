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

  State wait =                   State(NULL, NULL, NULL);
  State winAnimation =           State(TheWall::Display, NULL, StartTimerWallBeforeBlink);
  State gameOverAnimation =      State(TheBall::Move,    NULL, StartTimerWallBeforeBlink);
  State displayScore =           State(TheBall::Move,    NULL, StartTimerWallBeforeBlink);

  Pong() : Fsm(&wait){
    this->add_transition(&wait,              &winAnimation,      Events::ballHitedTheWall,        NULL);
    this->add_transition(&wait,              &gameOverAnimation, Events::ballErased,              NULL);
    this->add_transition(&winAnimation,      &wait,              Events::winAnimationIsOver,      NULL);
    this->add_transition(&gameOverAnimation, &displayScore,      Events::gameOverAnimationIsOver, NULL);
    
    Events::SetCheckEvents(Events::CheckEventsDuringGame);
  } 
};


float Pong::boardTilts[3];
Pong::Events::Event (* Pong::Events::checkEvents)();
int Pong::TheWall::wallPosition;

#endif
