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
  const int startPosition = 0;
  const int endPosition = 88;
  const int catchPosition = 60;
  const int motorIncrement = 1;
  const int delayBetweenPositionChange = 20;
  const int delayBeforeReturn = 500;
  
  void GoOneStep(int delayInMilisecond, int increment);
  void SetServoPosition(int position);

  
  public:
  Catapult();
  void Setup();
  bool ThrowMovement(int position);
  void ReturnMovement(int speed, int position);
  void CatchTheBall();
  void GoDownOneStep();
  void GoUpOneStep();
  
  void Test();
};

#endif
