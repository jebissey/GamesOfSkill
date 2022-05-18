#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor()
{  
}
 

long UltrasonicSensor::ReadDistance()
{
  long cumulDistance = 0;
  for(int i = 0; i <mesures; i++)
  {
    cumulDistance += sr04.Distance();
    delay(delayBetweenReads);    
  }
  return cumulDistance / mesures;
}

void UltrasonicSensor::DisplayDistance()
{
  long distance1, distance2;
  int mesures = 0;
  do {
    distance1 = ReadDistance();
    delay(delayBetweenMesures);
    distance2 = ReadDistance();
    delay(delayBetweenMesures);
    mesures++;
  } while(abs(distance1 - distance2) > 2);
  
  Serial.print(distance1);
  Serial.print(" (");
  Serial.print(mesures);
  Serial.println(") cm");
}

void UltrasonicSensor::DisplayMesure()
{ 
  Serial.println(ReadDistance());
}

void UltrasonicSensor::Test()
{
  DisplayDistance();
}
