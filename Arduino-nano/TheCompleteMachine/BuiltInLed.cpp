#include "BuiltInLed.h"

BuiltInLed::BuiltInLed()
{  
  pinMode(LED_BUILTIN, OUTPUT);
}

void BuiltInLed::Display(int halfTimeDuration)
{
  if(time.Delay(&timeInMs, timeInMs, halfTimeDuration))
  {
    ledStatus = !ledStatus;
    digitalWrite(LED_BUILTIN, ledStatus);
  } 
}  
