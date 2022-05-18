
#include "Catapult.h"

Catapult catapult;

void setup() 
{
  catapult.Setup();
}


void loop() 
{
  catapult.ThrowMovement(110);
  delay(1000);
  catapult.ReturnMovement(50, 0);
  delay(4000);                       
}
