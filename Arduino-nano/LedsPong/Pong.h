#ifndef PONG_H
#define PONG_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#include "Time.h"
static Time time;


#include <Fsm.h>

static unsigned long timerForMoveTheBall;
static unsigned long timerForWallStartBlink;

#include "Gy521.h"
#include "LedsSquare.h"

static const RowCol ballSize = RowCol(2, 2);
static LedsSquare ledsSquare = LedsSquare(ballSize);


class Pong : public Fsm {
private:
  State start =             State(InitStep, StartAnimation, NULL);
  State gaming =            State(StartGaming, Gaming, EndGaming);
  State winAnimation =      State(InitStep, WinAnimation, NewPoint);
  State gameOverAnimation = State(InitStep, GameOverAnimation, NULL);
  State displayScore =      State(DisplayScore, NULL, NewGame);
  
  static Gy_521 gy521;
  static float boardTilts[3];
    
#include "Pong.TheWall.h"
  TheWall theWall;
  
#include "Pong.TheBall.h"
  TheBall theBall;

#include "Pong.Events.h"
  Events events;

  static bool startGaming;
  static void StartGaming(){ startGaming = true; }
  static bool endGaming;
  static void EndGaming(){ endGaming = true; }
  static void Gaming(){ Serial.print("g"); }

  static int step;
  static void InitStep(){step= 0;}
  static bool GameAnimation(byte masks[], int sizeOfMasks, int animationTime = 100){
    int maxStep = sizeOfMasks - LedsSquare::matrixSize;
    static unsigned long animationTimer;
    if(time.IsOver(animationTime, &animationTimer)){
      Serial.print("_");
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
      
      B01001100,
      B10010010,
      B10010010,
      B10010010,
      B01100100,

      B00000000,
      
      B11111110,
      B00001000,
      B00001000,
      B11110000,
      
      B00000000,
      
      B01110000,
      B10001000,
      B10001000,
      B11110000,
      B10000000,
      
      B00000000,
      
      B11111110,
      B00010000,
      B00110000,
      B01001000,
      B10000000,
      
      B00000000,
      
      B01110000,
      B10101000,
      B10101000,
      B10010000,
     
      B00000000,
      B00000000,
      B00000000,
      
      B11111000,
      B00001000,
      B11111000,
      B00001000,
      B11110000,
      
      B00000000,
      
      B01110000,
      B10101000,
      B10101000,
      B10010000,
      
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
      B00000000,

      B10000001,
      B11111111,
      B10000001,
      
      B00000000,
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
    if(GameAnimation(gameOver, sizeof(gameOver), 50)) Events::gameEvent = Events::gameOverAnimationIsOver; 
  }
  
  static void DisplayScore(){
    Serial.println("\nDisplay score");
    
  }
  
  static void NewGame(){
    Serial.println("\nNew Game");
    
  }
    
  static void NewPoint(){
    Serial.println("\nNew Point");
    
  }
  
public: 
  void Setup(){
    gy521.Setup();
    randomSeed(3);
  }
  
  void Run(){
    theWall.run_machine();
    int wallEvent = events.GetWallEvent();
    theWall.trigger(wallEvent);
        
    theBall.run_machine();
    int ballEvent = events.GetBallEvent();
    theBall.trigger(ballEvent);

    run_machine();
    int gameEvent = events.GetGameEvent();
    trigger(gameEvent);



    delay(100);
    Serial.print("[");
    Serial.print(wallEvent);
    Serial.print(";");
    Serial.print(ballEvent);
    Serial.print(";");
    Serial.print(ballEvent);
    Serial.print("]");

    static unsigned long secondTime;
    if(time.IsOver(1000, &secondTime)){
      Serial.println("");
    }
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

  static bool IsGameStarting(bool reset = false){ 
    if(startGaming == true){
      if(reset) startGaming = false;
      return true;
    }
    return false;
  }

  static bool IsGameEnding(bool reset = false){ 
    if(endGaming == true){
      if(reset) endGaming = false;
      return true;
    }
    return false;
  }
};


float Pong::boardTilts[3];
int Pong::step;
int Pong::TheWall::wallPosition;
int Pong::TheBall::ballStatus;
unsigned long Pong::TheWall::beforeWallBlinkingTimer;
unsigned long Pong::TheWall::wallBlinkingTimer;
int Pong::Events::gameEvent;
int Pong::Events::wallEvent;
int Pong::Events::ballEvent;
bool Pong::startGaming;
bool Pong::endGaming;

#endif
