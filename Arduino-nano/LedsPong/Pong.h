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

#include "Gy521.h"
#include "LedsSquare.h"

static const RowCol ballSize = RowCol(2, 2);
static LedsSquare ledsSquare = LedsSquare(ballSize);


class Pong : public Fsm {
private:
  State wait =              State(NULL, WaitAnimation, NULL);
  State winAnimation =      State(NULL, WinAnimation, NULL);
  State gameOverAnimation = State(NULL, GameOverAnimation, NULL);
  State displayScore =      State(NULL, DisplayScore, NULL);
  
  const RowCol ballCoordonateAtStartUp = RowCol(3, 3);
  static Gy_521 gy521;
  static float boardTilts[3];
  static int gameEvent;

#include "Pong.TheWall.h"
  TheWall theWall;
  
#include "Pong.TheBall.h"
  TheBall theBall;

#include "Pong.Events.h"
  Events events;
  
  static void WinPoint(){
    Serial.println("WinPoint");
  }

  static void WaitAnimation(){ Serial.print("-"); }

  static void WinAnimation(){
    Serial.println("WinAnimation");
  }

  static void GameOverAnimation(){
    static byte masks[] = {
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B01111110,
      B10000001,
      B10010001,
      B10010001,
      B01100000,
      B00000000,
      B11111110,
      B00010001,
      B00010001,
      B00010001,
      B11111110,
      B00000000,
      B11111111,
      B00000010,
      B00000100,
      B00001000,
      B00000100,
      B00000010,
      B11111111,
      B00000000,
      B11111111,
      B10010001,
      B10010001,
      B10010001,
      B10000001,
      B00000000,
      B00000000,
      B00000000,
      B01111110,
      B10000001,
      B10000001,
      B10000001,
      B01111110,
      B00000000,
      B00111111,
      B01000000,
      B10000000,
      B01000000,
      B00111111,
      B00000000,
      B11111111,
      B10010001,
      B10010001,
      B10010001,
      B10000001,
      B00000000,
      B11111111,
      B00010001,
      B00110001,
      B01010001,
      B10001110,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
    };
    static const int maxStep = sizeof(masks) - LedsSquare::matrixSize;
    static int step = 0;
    static int mask;
    static const int animationTime = 100;
    static unsigned long animationTimer;
    if(time.IsOver(animationTime, &animationTimer)){
      if(step++ > maxStep){
          gameEvent = Events::gameOverAnimationIsOver; 
          step = 0;
      }
      else{
        for(int i = 0; i < LedsSquare::matrixSize; i++){
          ledsSquare.setRow(0, i,masks[step + i]);
        }
      }
    }
  }
  
  static void DisplayScore(){
    Serial.print("*");
    
  }
  
public: 
  void Setup(){
    gy521.Setup();
    ledsSquare.MoveAbsolute(ballCoordonateAtStartUp);
  }
  
  void Run(){
    theWall.run_machine();
    theWall.trigger(events.GetWallEvent());
        
    theBall.run_machine();
    theBall.trigger(events.GetBallEvent());

    run_machine();
    trigger(events.GetGameEvent());
  }

  Pong() : Fsm(&wait){
    this->add_transition(&wait,              &winAnimation,      Events::ballHitTheWall,          NULL);
    this->add_transition(&wait,              &gameOverAnimation, Events::ballErased,              NULL);
    this->add_transition(&wait,              &gameOverAnimation, Events::wallErased,              NULL);
    this->add_transition(&winAnimation,      &wait,              Events::winAnimationIsOver,      NULL);
    this->add_transition(&gameOverAnimation, &displayScore,      Events::gameOverAnimationIsOver, NULL);

    gameEvent = Events::nothing;
  } 

  static int GetEvent(){ return gameEvent; }
};


float Pong::boardTilts[3];
int Pong::TheWall::wallPosition;
int Pong::TheWall::wallEvent;
int Pong::TheBall::ballStatus;
unsigned long Pong::TheWall::beforeWallBlinkingTimer;
unsigned long Pong::TheWall::wallBlinkingTimer;
int Pong::Events::gameEvent;
int Pong::gameEvent;

#endif
