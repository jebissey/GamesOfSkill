
#include "BuiltInLed.h"
#include "Catapult.h"
#include "Joystick.h"
#include "Pulley.h"
#include "Time.h"
#include "UltrasonicSensor.h"

BuiltInLed builtInLed;
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
  builtInLed.Display(500);
  ultrasonicSensor.ReadDistance();
  
  if(joystick.JoystickPressed())
  {
    if(catapult.ThrowMovement(55))
    {
      ultrasonicSensor.DisplayDistance();
    }
  }
  
  pulley.Move(map(-joystick.GetX(), joystick.xyMinSent, joystick.xyMaxSent, -256, 256));

  if(joystick.IsExtremePositionY() > 0) catapult.GoUpOneStep();
  if(joystick.IsExtremePositionY() < 0) catapult.GoDownOneStep();


    static unsigned long second;
    Time myTime;
    if(myTime.NewSecond(&second, second))
    {          
      ultrasonicSensor.DisplayMesure();
    }
}

void TestMode()
{
  joystick.Test();
  pulley.Test();
  catapult.Test();
}
