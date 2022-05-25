#ifndef CATAPULT_H
#define CATAPULT_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "PinsEnum.h"
#include <Servo.h>

class Catapult : public Servo
{
  private:
  const int endPosition = 88;
  const int catchPosition = 56;
  const int motorIncrement = 1;
  const int delayBeforeReturn = 500;
  
  void GoOneStep(int delayInMilisecond, int increment);
  void SetServoPosition(int position);

  
  public:
  const int startPosition = 0;
  const int delayBetweenPositionChange = 20;
  
  Catapult();
  void Setup();

  int GetPosition();
  
  void GoDown(int delayBetweenPositionChange, int position);
  void GoUp(int position);

  void GoDownOneStep();
  void GoUpOneStep();

  
  void Test();
};

#endif
