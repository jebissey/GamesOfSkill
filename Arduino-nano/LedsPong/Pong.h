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
  static const int scoreMax = 64;
  static int winDelay;

  State start =             State(InitStep, StartAnimation, NewGame);
  State gaming =            State(StartGaming, NULL, EndGaming);
  State winAnimation =      State(InitStep, WinAnimation, NewPoint);
  State gameOverAnimation = State(InitStep, GameOverAnimation, NULL);
  State displayScore =      State(DisplayScore, NULL, NULL);

  
  static Gy_521 gy521;
  static float boardTilts[3];
  static int points;
    
#include "Pong.TheWall.h"
  TheWall theWall;
  
#include "Pong.TheBall.h"
  TheBall theBall;

#include "Pong.Events.h"
  Events events;

#include "Pong.Animation.h"
  static void StartAnimation(){Animation::StartAnimation(); }
  static void WinAnimation(){Animation::WinAnimation(points); }
  static void GameOverAnimation(){Animation::GameOverAnimation(); }
  

  static bool startGaming;
  static void StartGaming(){ startGaming = true; }
  
  static bool endGaming;
  static void EndGaming(){ endGaming = true; }

  static void InitStep(){ Animation::InitStep();}
  
  static void DisplayScore(){
    ledsSquare.ClearDisplay();;
    ledsSquare.DisplayPoints(points);
  }
  
  static void NewGame(){
    points = 0;
    winDelay = scoreMax;
    TheWall::ResetDifficulty();
    Events::ResetEvents();
  }
    
  static void NewPoint(){
    if(++points >= scoreMax) Events::gameEvent = Events::maxScoreReached;
    winDelay--;
    TheWall::IncreaseDifficulty();
    Events::ResetEvents();
  }
  
public: 
  void Setup(){
    gy521.Setup();
    randomSeed(analogRead(0));
    NewGame();
  }
  
  void Run(){
    theWall.run_machine();
    theWall.trigger(events.GetWallEvent());
        
    theBall.run_machine();
    theBall.trigger(events.GetBallEvent());

    run_machine();
    trigger(events.GetGameEvent());

    delay(1);
  }

  static void StartToGamming(){ Serial.println("G: StartToGamming (board shaked)");}
  static void GamingToWinAnimation(){ Serial.println("G: GamingToWinAnimation (ball hit the wall)");}
  static void GamingToGameOverAnimation1(){ Serial.println("G: GamingToGameOverAnimation (ball erased)");}
  static void GamingToGameOverAnimation2(){ Serial.println("G: GamingToGameOverAnimation (wall erased)");}
  static void GamingToDisplayScore(){ Serial.println("G: GamingToDisplayScore (max score reached)");}
  static void WinAnimationToGaming(){ Serial.println("G: WinAnimationToGaming (win animation is over)");}
  static void gameOverAnimationToDisplayScore(){ Serial.println("G: gameOverAnimationToDisplayScore (game over animation is over)");}
  static void DisplayScoreToStart(){ Serial.println("G: DisplayScoreToStart (board shaked)");}

  Pong() : Fsm(&start){
    this->add_transition(&start,             &gaming,            Events::boardShaked, StartToGamming);
    this->add_transition(&gaming,            &winAnimation,      Events::ballHitTheWall, GamingToWinAnimation);
    this->add_transition(&gaming,            &gameOverAnimation, Events::ballErased, GamingToGameOverAnimation1);
    this->add_transition(&gaming,            &gameOverAnimation, Events::wallErased, GamingToGameOverAnimation2);
    this->add_transition(&gaming,            &displayScore,      Events::maxScoreReached, GamingToDisplayScore);
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
int   Pong::winDelay;

int Pong::Animation::step;

int   Pong::Events::ballEvent;
int   Pong::Events::externalGameEvent;
int   Pong::Events::gameEvent;
int   Pong::Events::lastExternalGameEvent;
int   Pong::Events::wallEvent;

int   Pong::TheBall::ballStatus;
int   Pong::TheBall::step;

int           Pong::TheWall::beforeWallBlinkingTime;
unsigned long Pong::TheWall::beforeWallBlinkingTimer;
int           Pong::TheWall::step;
int           Pong::TheWall::wallBlinkingTime;
unsigned long Pong::TheWall::wallBlinkingTimer;
int           Pong::TheWall::wallPosition;

#endif
