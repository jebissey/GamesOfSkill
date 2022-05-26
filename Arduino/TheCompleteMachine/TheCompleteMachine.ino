
#include "Ball.h"
#include "BuiltInLed.h"
#include "Catapult.h"
#include "Joystick.h"
#include "LcdDisplay.h"
#include "PhotoCell.h"
#include "Pulley.h"
#include "Time.h"
#include "UltrasonicSensor.h"

Ball ball;
BuiltInLed builtInLed;
Catapult catapult;
Joystick joystick;
LcdDisplay lcdDisplay;
PhotoCell photoCell;
Pulley pulley;
UltrasonicSensor ultrasonicSensor;


enum {test_Mode, manual_mode};
int mode = manual_mode;
const int throwAngle = 55;

Time time;
unsigned long tenSeconds;
const int delayInMs = 500;


void setup() 
{
  Serial.begin(9600);

  catapult.Setup();
}

void loop() 
{
  switch(mode)
  {
    case test_Mode: 
    TestMode();
    break;

    case manual_mode: 
    ManualMode();
    break;
  }
}

void ManualMode()
{
  builtInLed.Display(delayInMs);
  ultrasonicSensor.ReadDistance();
  lcdDisplay.SwitchOff();
  
  if(joystick.JoystickPressed())
  {
    if(ball.Throw(catapult, throwAngle))
    {
      String mesuredDistance = String(ultrasonicSensor.ReadDistance());
      lcdDisplay.Write("Distance=" + mesuredDistance);
      ball.Catch();
    }
  }

  MovePulleyAndDisplayDistance();
  MoveCatapultAndDisplayPosition();
}

void MovePulleyAndDisplayDistance()
{
  int joystickX = -joystick.GetX();
  if(joystickX != 0)
  {
    pulley.Move(map(joystickX, joystick.xyMinSent, joystick.xyMaxSent, pulley.rotationalIncrement, -pulley.rotationalIncrement));
      
    String mesuredDistance = String(ultrasonicSensor.ReadDistance());
    lcdDisplay.Write("Distance=" + mesuredDistance + "   ");

    String mesuredLight = String(photoCell.Get());
    lcdDisplay.Write("Light=" + mesuredLight,0, 1);
  }
}

void MoveCatapultAndDisplayPosition()
{
  
  if(joystick.IsExtremePositionY() > 0)
  {
    catapult.GoUpOneStep();
    DisplayCatapultPosition();
  }
  if(joystick.IsExtremePositionY() < 0)
  {
    catapult.GoDownOneStep(); 
    DisplayCatapultPosition();
  }
}

void DisplayCatapultPosition()
{
  String servoPosition = String(catapult.GetPosition());
  lcdDisplay.Write("catapult=" + servoPosition + "   ");
}

void TestMode()
{
  joystick.Test();
  pulley.Test();
  catapult.Test();
}
