
void setup() 
{
 ServoSetup();
 JoystickSetup();
 StepperMotorSetup();
 UltrasonicSensorSetup();
 Serial.begin(9600);
}

void loop() 
{
  if(JoystickPressed())
  {
    if(Throw (70))
    {
      DisplayDistance();
    }
  }
  
  PulleyMove();

  if(IsExtremePositionY() > 0)
  {
    CatchTheBall();
  }
  
  if(IsExtremePositionY() < 0)
  {
    GoDownOneStep();
  }
}


// ======================================================================
// Ultrasonic sensor
#include "SR04.h"
const int trig = 12;
const int echo = 13;
const int mesures = 5;

SR04 sr04 = SR04(echo,trig);

void UltrasonicSensorSetup()
{
 //sr04 = SR04(echo,trig);
}

long ReadDistance()
{
  long cumulDistance = 0;
  for(int i = 0; i <mesures; i++)
  {
    cumulDistance += sr04.Distance();
    delay(25);    
  }
  return cumulDistance / mesures;
}

void DisplayDistance()
{
  long distance1, distance2;
  int mesures = 0;
  do {
    distance1 = ReadDistance();
    delay(100);
    distance2 = ReadDistance();
    delay(100);
    mesures++;
  } while(abs(distance1 - distance2) > 2);
  Serial.print(distance1);
  Serial.print(" (");
  Serial.print(mesures);
  Serial.println(") cm");
}
// ======================================================================
// Pulley with stepper motor

#include <Stepper.h> 
const int stepperMotorSteps = 2048;
const int rotationalIncrement = stepperMotorSteps / 128;
const int in1 = 8;
const int in2 = 9;
const int in3 = 10;
const int in4 = 11;
const int speed = 16; // [1 .. 16]

Stepper pulley(stepperMotorSteps, in1, in3, in2, in4);

void StepperMotorSetup()
{
 //Stepper pulley = Stepper(stepperMotorSteps, in1, in3, in2, in4);
 pulley.setSpeed(speed);
}

void PulleyMove()
{
  int steps = GetJoystickX();
  if(steps != 0)
  {
    pulley.step(steps);
  }
}


// ======================================================================
// Joystick
const int xAxe = 0;
const int yAxe = 1;
const int buttonPressed = 2;

const int xyMin = 0;
const int xyMax = 1020;
const int neutralPosition = (xyMax - xyMin) / 2;
const int neutralPositionWidth = 150;
const int extremePositionWidth = 50;

void JoystickSetup()
{
  pinMode(buttonPressed, INPUT);
  digitalWrite(buttonPressed, HIGH);
}

int GetJoystickX()
{
  return GetJoystickXY(analogRead(xAxe));
}

int GetJoystickY()
{
  return GetJoystickXY(analogRead(yAxe));
}

int GetJoystickXY(int position)
{
  if(IsNeutralPosition(position)) return 0;
  if(position > neutralPosition)
  {
    return -rotationalIncrement;
  }
  return rotationalIncrement;
}

bool JoystickPressed()
{
  return digitalRead(buttonPressed) == 0;
}

bool IsNeutralPosition(int position)
{
  return abs(neutralPosition - position) < neutralPositionWidth;
}

int IsExtremePositionX()
{
  return IsExtremePosition(analogRead(xAxe));
}

int IsExtremePositionY()
{
  return IsExtremePosition(analogRead(yAxe));
}

int IsExtremePosition(int position)
{
  if( xyMax - position < extremePositionWidth) return 1;
  if( position + xyMin < extremePositionWidth) return -1;
  return 0;
}

// ======================================================================
// Catapult with servo motor

#include <Servo.h>
const int servoPin = 7;
const int startPosition = 0;
const int endPosition = 110;
const int catchPosition = 50;
const int increment = 1;
const int delayBetweenPositionChange = 20;

Servo catapult;

void ServoSetup()
{
  catapult.attach(servoPin);
  SetServoPosition(startPosition);
}

bool Throw(int position)
{
  if(catapult.read() > startPosition)
  {
     Return(delayBetweenPositionChange, startPosition);
     return false;
  }
  SetServoPosition(position);
  delay(500);
  Return(delayBetweenPositionChange, catchPosition);
  return true;
}

void Return(int speed, int position)
{
  while (catapult.read() > position) 
  {
    GoDownOneStep(speed);
  }
  SetServoPosition(position);
}

void CatchTheBall()
{
  SetServoPosition(catchPosition);
}

void GoDownOneStep()
{
  GoDownOneStep(delayBetweenPositionChange * 20);
}
void GoDownOneStep(int delayInMilisecond)
{
  int pos = catapult.read();
  SetServoPosition(pos - increment);  
  delay(delayInMilisecond);
}

void SetServoPosition(int position)
{
  if(position >= startPosition && position <= endPosition)
  {
    catapult.write(position); 
  }
}
// ======================================================================
