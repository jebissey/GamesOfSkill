#include "Catapult.h"

Catapult::Catapult()
{
  pinMode(servoMotor_pin, OUTPUT); 
}

void Catapult::Setup()
{
  this->attach(servoMotor_pin);
  SetServoPosition(startPosition);
}

void Catapult::GoUp(int position)
{
  SetServoPosition(position);
}

void Catapult::GoDown(int delayBetweenPositionChange, int position)
{
  while (this->read() > position) GoOneStep(delayBetweenPositionChange, -motorIncrement);
  SetServoPosition(position);
}

void Catapult::GoDownOneStep() { GoOneStep(delayBetweenPositionChange, -motorIncrement); }
void Catapult::GoUpOneStep()   { GoOneStep(delayBetweenPositionChange, motorIncrement); }

void Catapult::GoOneStep(int delayInMilisecond, int increment)
{
  int pos = this->read();
  SetServoPosition(pos + increment);  
  delay(delayInMilisecond);
}

void Catapult::SetServoPosition(int position)
{
  if(position >= startPosition && position <= endPosition) this->write(position); 
}

int Catapult::GetPosition()
{
  Serial.println(this->read());
  return this->read(); 
}


void Catapult::Test()
{

}
