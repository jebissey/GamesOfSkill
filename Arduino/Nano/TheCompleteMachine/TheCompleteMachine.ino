
#include "BuiltInLed.h"
#include "Catapult.h"
#include "Joystick.h"
#include "LcdDisplay.h"
#include "PhotoCell.h"
#include "Pulley.h"
#include "Time.h"
#include "UltrasonicSensor.h"

BuiltInLed builtInLed;
Catapult catapult;
Joystick joystick;
LcdDisplay lcdDisplay;
PhotoCell photoCell;
Pulley pulley;
UltrasonicSensor ultrasonicSensor;


enum {test_Mode, manual_mode};
int mode = manual_mode;


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
    if(catapult.ThrowMovement(55))
    {
      String mesuredDistance = String(ultrasonicSensor.ReadDistance());
      lcdDisplay.Write("Distance=" + mesuredDistance);
    }
  }

  int joystickX = -joystick.GetX();
  if(joystickX != 0)
  {
    pulley.Move(map(joystickX, joystick.xyMinSent, joystick.xyMaxSent, pulley.rotationalIncrement, -pulley.rotationalIncrement));
      
    String mesuredDistance = String(ultrasonicSensor.ReadDistance());
    lcdDisplay.Write("Distance=" + mesuredDistance + "   ");

    String mesuredLight = String(photoCell.Get());
    lcdDisplay.Write("Light=" + mesuredLight,0, 1);
  }

  if(joystick.IsExtremePositionY() > 0) catapult.GoUpOneStep();
  if(joystick.IsExtremePositionY() < 0) catapult.GoDownOneStep();


  if(time.Delay(&tenSeconds, tenSeconds, 2000))
  {          
    
    //Serial.println("Light=" + mesuredLight);
  }
  
}

void TestMode()
{
  joystick.Test();
  pulley.Test();
  catapult.Test();
}
