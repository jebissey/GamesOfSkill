
#include "Catapult.h"
#include "Joystick.h"
#include "Pulley.h"
#include "Time.h"
#include "UltrasonicSensor.h"

Catapult catapult;
Joystick joystick;
Pulley pulley;
UltrasonicSensor ultrasonicSensor;


enum {test_Mode, manual_mode};
int mode = manual_mode;


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
  if(joystick.JoystickPressed())
  {
    if(catapult.ThrowMovement(70))
    {
      ultrasonicSensor.DisplayDistance();
    }
  }
  
  pulley.Move(-joystick.GetX());

  if(joystick.IsExtremePositionY() < 0) catapult.GoUpOneStep();
  if(joystick.IsExtremePositionY() > 0) catapult.GoDownOneStep();


    static unsigned long deciSecond;
    Time myTime;
    if(myTime.NewDeciSecond(&deciSecond, deciSecond))
    {          
      if(deciSecond % 10 == 9)
      {
        ultrasonicSensor.DisplayMesure();
      }
    }
}

void TestMode()
{
  joystick.Test();
  pulley.Test();
  catapult.Test();
}
