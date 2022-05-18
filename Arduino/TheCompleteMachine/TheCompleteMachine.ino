
#include "Catapult.h"
#include "Joystick.h"
#include "Pulley.h"
#include "UltrasonicSensor.h"

Catapult catapult();
Joystick joystick;
Pulley pulley;
UltrasonicSensor ultrasonicSensor;


void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  /*
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
*/
// /*
  joystick.Test();
  pulley.Test();
  //catapult.Test();
// */
}
