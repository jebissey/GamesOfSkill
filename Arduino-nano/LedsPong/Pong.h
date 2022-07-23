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
  State start =             State(NULL, StartAnimation, NULL);
  State gaming =            State(NULL, Gaming, NULL);
  State winAnimation =      State(NULL, WinAnimation, NULL);
  State gameOverAnimation = State(NULL, GameOverAnimation, NULL);
  State displayScore =      State(DisplayScore, NULL, NULL);
  
  const RowCol ballCoordonateAtStartUp = RowCol(3, 3);
  static Gy_521 gy521;
  static float boardTilts[3];
    
#include "Pong.TheWall.h"
  TheWall theWall;
  
#include "Pong.TheBall.h"
  TheBall theBall;

#include "Pong.Events.h"
  Events events;
  
  static void Gaming(){ Serial.print("g"); }

  static bool GameAnimation(byte masks[], int sizeOfMasks, int animationTime = 100){
    static const int maxStep = sizeOfMasks - LedsSquare::matrixSize;
    static int step = 0;
    static int mask;
    static unsigned long animationTimer;
    if(time.IsOver(animationTime, &animationTimer)){
      if(step++ > maxStep) step = 0;
      else{
        for(int i = 0; i < LedsSquare::matrixSize; i++){
          ledsSquare.setRow(0, i, masks[step + i]);
        }
      }
    }
    return step == 0;
  }

  static void StartAnimation(){
    byte shakeMe[] = {
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      
      B01001110,
      B10010001,
      B10010001,
      B10010001,
      B01100010,

      B00000000,
      B00000000,
      
      B11111111,
      B00010000,
      B00010000,
      B00010000,
      B11111111,
      
      B00000000,
      B00000000,
      
      B11111110,
      B00010001,
      B00010001,
      B00010001,
      B11111110,
      
      B00000000,
      B00000000,
      
      B11111111,
      B00010000,
      B00010000,
      B00101000,
      B11000111,
      
      B00000000,
      B00000000,
      
      B11111111,
      B10010001,
      B10010001,
      B10010001,
      B10000001,
     
      B00000000,
      B00000000,
      B00000000,
      
      B11111111,
      B00000010,
      B00000100,
      B00001000,
      B00000100,
      B00000010,
      B11111111,
      
      B00000000,
      B00000000,
      
      B11111111,
      B10010001,
      B10010001,
      B10010001,
      B10000001,
      
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
    };
    GameAnimation(shakeMe, sizeof(shakeMe), 200); 
  }
  
  static void WinAnimation(){
    byte win[] = {
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      
      B00111111,
      B01000000,
      B10000000,
      B01000000,
      B00100000,
      B01000000,
      B10000000,
      B01000000,
      B00111111,
      
      B00000000,
      
      B11111111,
      
      B00000000,
      
      B11111111,
      B00000010,
      B00000100,
      B00001000,
      B00010000,
      B00100000,
      B01000000,
      B11111111,
      
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
    };
    if(GameAnimation(win, sizeof(win))) Events::gameEvent = Events::winAnimationIsOver; 
  }
  
  static void GameOverAnimation(){
    byte gameOver[] = {
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
    if(GameAnimation(gameOver, sizeof(gameOver))) Events::gameEvent = Events::gameOverAnimationIsOver; 
  }
  
  static void DisplayScore(){
    Serial.println("\nDisplay score");
    
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

  Pong() : Fsm(&start){
    this->add_transition(&start,             &gaming,            Events::boardShaked, NULL);
    this->add_transition(&gaming,            &winAnimation,      Events::ballHitTheWall, NULL);
    this->add_transition(&gaming,            &gameOverAnimation, Events::ballErased, NULL);
    this->add_transition(&gaming,            &gameOverAnimation, Events::wallErased, NULL);
    this->add_transition(&winAnimation,      &gaming,            Events::winAnimationIsOver, NULL);
    this->add_transition(&gameOverAnimation, &displayScore,      Events::gameOverAnimationIsOver, NULL);
    this->add_transition(&displayScore,      &gaming,            Events::boardShaked, NULL);

    Events::gameEvent = Events::nothing;
  } 
};


float Pong::boardTilts[3];
int Pong::TheWall::wallPosition;
int Pong::TheBall::ballStatus;
unsigned long Pong::TheWall::beforeWallBlinkingTimer;
unsigned long Pong::TheWall::wallBlinkingTimer;
int Pong::Events::gameEvent;
int Pong::Events::wallEvent;
int Pong::Events::ballEvent;

#endif
