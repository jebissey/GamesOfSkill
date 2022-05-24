#include "Pulley.h"

Pulley::Pulley()
{  
  pulleyStepMotor.setSpeed(speed);
}

void Pulley::Move(int steps)
{
  if(steps != 0) pulleyStepMotor.step(steps);
} 


void Pulley::Test()
{
  Move(stepperMotorSteps / 4);
  delay(100);
  Move(-stepperMotorSteps / 4);
  delay(400);
} 
