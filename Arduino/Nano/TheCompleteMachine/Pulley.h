#ifndef PULLEY_H
#define PULLEY_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "AAA_PinsEnum.h"
#include <Stepper.h> 

class Pulley
{
  private:
  int cumuledSteps;
  
  const int stepperMotorSteps = 2048;
  const int speed = 16; // [1 .. 16]
  Stepper pulleyStepMotor = Stepper(stepperMotorSteps, stepperMotor_in1, stepperMotor_in3, stepperMotor_in2, stepperMotor_in4);

  public:
  const int rotationalIncrement = stepperMotorSteps / 32;
  
  Pulley();
  void Move(int steps);
  
  void Test();
};

#endif
