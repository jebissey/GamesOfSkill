#ifndef PULLEY_H
#define PULLEY_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Stepper.h> 

class Pulley
{
  private:
  const int stepperMotorSteps = 2048;
  const int rotationalIncrement = stepperMotorSteps / 128;
  const int speed = 16; // [1 .. 16]
  enum 
  {
  stepperMotor_in1 = 6,
  stepperMotor_in2 = 7,
  stepperMotor_in3 = 8,
  stepperMotor_in4 = 9,
  };
  
  Stepper pulleyStepMotor = Stepper(stepperMotorSteps, stepperMotor_in1, stepperMotor_in3, stepperMotor_in2, stepperMotor_in4);

  public:
  Pulley();
  void Move(int steps);
  
  void Test();
};

#endif
