
#include "BuiltInLed.h"
#include "Catapult.h"
#include "Joystick.h"
#include "LcdDisplay.h"
#include "Pulley.h"
#include "Time.h"
#include "UltrasonicSensor.h"

BuiltInLed builtInLed;
Catapult catapult;
Joystick joystick;
LcdDisplay lcdDisplay;
Pulley pulley;
UltrasonicSensor ultrasonicSensor;


enum {test_Mode, manual_mode};
int mode = manual_mode;


Time time;
unsigned long tenSeconds;


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
  builtInLed.Display(500);
  ultrasonicSensor.ReadDistance();
  lcdDisplay.SwitchOff();
  
  if(joystick.JoystickPressed())
  {
    if(catapult.ThrowMovement(55))
    {
      String mesuredDistance = String(ultrasonicSensor.ReadDistance());
      lcdDisplay.Write("Distance=" + mesuredDistance);
    }
  }
  
  pulley.Move(map(-joystick.GetX(), joystick.xyMinSent, joystick.xyMaxSent, pulley.rotationalIncrement, -pulley.rotationalIncrement));

  if(joystick.IsExtremePositionY() > 0) catapult.GoUpOneStep();
  if(joystick.IsExtremePositionY() < 0) catapult.GoDownOneStep();


  if(time.NewTenSeconds(&tenSeconds, tenSeconds))
  {          
    //lcdDisplay.Write(String(ultrasonicSensor.ReadDistance()));
    //lcdDisplay.Write("!");
  }
  
}

void TestMode()
{
  joystick.Test();
  pulley.Test();
  catapult.Test();
}
