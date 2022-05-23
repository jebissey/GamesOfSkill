#include "BuiltInLed.h"

BuiltInLed::BuiltInLed()
{  
  pinMode(LED_BUILTIN, OUTPUT);
}

void BuiltInLed::Display(int halfTimeDuration)
{
  static boolean ledStatus;
  static unsigned long time;
  
  if((millis() - time) > halfTimeDuration)
  {
    time = millis();
    ledStatus = !ledStatus;
    digitalWrite(LED_BUILTIN, ledStatus);
  } 
}  
