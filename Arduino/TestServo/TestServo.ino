
#include <Servo.h>



void setup() 
{
 ServoSetup();
}

void loop() 
{
  
  Throw (70);
  delay(500);
  Return();
    delay(5000);                       

}


// Catapult
const int servoPin = 9;
const int startPosition = 0;
const int endPosition = 110;
const int increment = 5;
const int delayBetweenPositionChange = 15;

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
  for (pos; pos > startPosition; pos -= 2) 
  {
    SetServoPosition(pos);  
    delay(delayBetweenPositionChange * 5);
  }
}
  
void SetServoPosition(int position)
{
  if(position >= startPosition && position <= endPosition)
  {
    catapult.write(position); 
  }
}
