#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor()
{  
}
 

long UltrasonicSensor::ReadDistance()
{
  static long lastDistance = 0;
  long newlDistance = sr04.Distance();
  long averageDistance = (lastDistance + newlDistance) / 2;
  lastDistance = newlDistance;
  return averageDistance;
}


void UltrasonicSensor::Test()
{
  const int delayBetweenMesures = 100;
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
