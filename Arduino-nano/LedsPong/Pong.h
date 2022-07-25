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
  State gaming =            State(StartGaming, NULL, EndGaming);
  State winAnimation =      State(InitStep, WinAnimation, NewPoint);
  State gameOverAnimation = State(InitStep, GameOverAnimation, NULL);
  State displayScore =      State(DisplayScore, NULL, NewGame);
  
  static Gy_521 gy521;
  static float boardTilts[3];
  static int points;
    
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

  static int step;
  static void InitStep(){step = 0;}
  
  static bool GameAnimation(byte masks[], int sizeOfMasks, int animationTime = 100){
    int maxStep = sizeOfMasks - LedsSquare::matrixSize;
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
    GameAnimation(shakeMe, sizeof(shakeMe)); 
  }
  
  static void WinAnimation(){
    byte win[] = {
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      
      B00111110,
      B11000000,
      B01100000,
      B11000000,
      B00111110,
      
      B00000000,

      B00010000,
      B01111010,
      B10000000,
      B01000000,
      
      B00000000,
      
      B11111000,
      B00001000,
      B11110000,
      
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
    };
    if(GameAnimation(win, sizeof(win), 75)) Events::gameEvent = Events::winAnimationIsOver; 
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
    if(GameAnimation(gameOver, sizeof(gameOver), 75)) Events::gameEvent = Events::gameOverAnimationIsOver; 
  }
  
  static void DisplayScore(){
    ledsSquare.ClearDisplay();;
    ledsSquare.DisplayPoints(points);
  }
  
  static void NewGame(){
    points = 0;
    TheWall::ResetDifficulty();
    Events::ResetEvents();
  }
    
  static void NewPoint(){
    points++;
    TheWall::IncreaseDifficulty();
    Events::ResetEvents();
  }
  
public: 
  void Setup(){
    gy521.Setup();
    randomSeed(analogRead(0));
  }
  
  void Run(){
    theWall.run_machine();
    theWall.trigger(events.GetWallEvent());
        
    theBall.run_machine();
    theBall.trigger(events.GetBallEvent());

    run_machine();
    trigger(events.GetGameEvent());

    //delay(25);
  }

  static void StartToGamming(){ Serial.println("Game: StartToGamming");}
  static void GamingToWinAnimation(){ Serial.println("Game: GamingToWinAnimation");}
  static void GamingToGameOverAnimation1(){ Serial.println("Game: GamingToGameOverAnimation1");}
  static void GamingToGameOverAnimation2(){ Serial.println("Game: GamingToGameOverAnimation2");}
  static void WinAnimationToGaming(){ Serial.println("Game: WinAnimationToGaming");}
  static void gameOverAnimationToDisplayScore(){ Serial.println("Game: gameOverAnimationToDisplayScore");}
  static void DisplayScoreToStart(){ Serial.println("Game: DisplayScoreToStart");}

  Pong() : Fsm(&start){
    this->add_transition(&start,             &gaming,            Events::boardShaked, StartToGamming);
    this->add_transition(&gaming,            &winAnimation,      Events::ballHitTheWall, GamingToWinAnimation);
    this->add_transition(&gaming,            &gameOverAnimation, Events::ballErased, GamingToGameOverAnimation1);
    this->add_transition(&gaming,            &gameOverAnimation, Events::wallErased, GamingToGameOverAnimation2);
    this->add_transition(&winAnimation,      &gaming,            Events::winAnimationIsOver, WinAnimationToGaming);
    this->add_transition(&gameOverAnimation, &displayScore,      Events::gameOverAnimationIsOver, gameOverAnimationToDisplayScore);
    this->add_transition(&displayScore,      &start,             Events::boardShaked, DisplayScoreToStart);

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
bool  Pong::endGaming;
int   Pong::points;
bool  Pong::startGaming;
int   Pong::step;

int   Pong::Events::ballEvent;
int   Pong::Events::externalGameEvent;
int   Pong::Events::gameEvent;
int   Pong::Events::lastExternalGameEvent;
int   Pong::Events::wallEvent;

int   Pong::TheBall::ballStatus;

int           Pong::TheWall::beforeWallBlinkingTime;
unsigned long Pong::TheWall::beforeWallBlinkingTimer;
int           Pong::TheWall::step;
int           Pong::TheWall::wallBlinkingTime;
unsigned long Pong::TheWall::wallBlinkingTimer;
int           Pong::TheWall::wallPosition;

#endif
