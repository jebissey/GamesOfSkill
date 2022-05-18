
#include <Servo.h>

void setup() 
{
 ServoSetup();
}

void loop() 
{
  Throw (90);
  delay(1000);
  Return();
  delay(4000);                       
}


// Catapult
const int servoPin = 7;
const int startPosition = 0;
const int endPosition = 110;
const int increment = 5;
const int delayBetweenPositionChange = 25;

Servo catapult;

void ServoSetup()
{
  catapult.attach(servoPin);
  SetServoPosition(startPosition);
}

void Throw(int lastPosition)
{
  SetServoPosition(lastPosition);
}

void Return()
{
  int pos = catapult.read();
  for (pos; pos > startPosition; pos -= increment) 
  {
    SetServoPosition(pos);  
    delay(delayBetweenPositionChange);
  }
}
  
void SetServoPosition(int position)
{
  if(position >= startPosition && position <= endPosition)
  {
    catapult.write(position); 
  }
}
