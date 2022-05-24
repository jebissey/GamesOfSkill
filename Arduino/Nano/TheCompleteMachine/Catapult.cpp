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

bool Catapult::ThrowMovement(int position)
{
  if(this->read() > startPosition)
  {
     ReturnMovement(delayBetweenPositionChange, startPosition);
     return false;
  }
  SetServoPosition(position);
  delay(delayBeforeReturn);
  ReturnMovement(delayBetweenPositionChange, catchPosition);
  return true;
}

void Catapult::ReturnMovement(int speed, int position)
{
  while (this->read() > position) GoOneStep(speed, -motorIncrement);
  SetServoPosition(position);
}

void Catapult::CatchTheBall()  { SetServoPosition(catchPosition); }
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


void Catapult::Test()
{
  Serial.print("Servo=");
  Serial.println(this->read());
  ThrowMovement(endPosition );
  
  Serial.print("Servo=");
  Serial.println(this->read());
  
  ReturnMovement(delayBetweenPositionChange, startPosition);
  
  Serial.print("Servo=");
  Serial.println(this->read());
}
