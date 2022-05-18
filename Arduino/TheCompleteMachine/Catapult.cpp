#include "Catapult.h"

Catapult::Catapult()
{
  servoCatapult.attach(servoMotor_pin);
  SetServoPosition(startPosition);
}

bool Catapult::ThrowMovement(int position)
{
  if(servoCatapult.read() > startPosition)
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
  while (servoCatapult.read() > position) GoOneStep(speed, -motorIncrement);
  SetServoPosition(position);
}

void Catapult::CatchTheBall()  { SetServoPosition(catchPosition); }
void Catapult::GoDownOneStep() { GoOneStep(delayBetweenPositionChange * 20, -motorIncrement); }
void Catapult::GoUpOneStep()   { GoOneStep(delayBetweenPositionChange * 20, motorIncrement); }

void Catapult::GoOneStep(int delayInMilisecond, int increment)
{
  int pos = servoCatapult.read();
  SetServoPosition(pos + increment);  
  delay(delayInMilisecond);
}

void Catapult::SetServoPosition(int position)
{
  if(position >= startPosition && position <= endPosition) servoCatapult.write(position); 
}

void Catapult::Test()
{
  Serial.print("Servo=");
  Serial.println(servoCatapult.read());
  ThrowMovement(endPosition );
  
  Serial.print("Servo=");
  Serial.println(servoCatapult.read());
  
  ReturnMovement(delayBetweenPositionChange, startPosition);
  
  Serial.print("Servo=");
  Serial.println(servoCatapult.read());
}
