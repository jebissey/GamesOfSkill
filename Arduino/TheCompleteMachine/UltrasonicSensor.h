#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

#include <SR04.h>

class UltrasonicSensor
{
  private:
  enum 
  {
    UltrasonicSensor_trig = 12,
    UltrasonicSensor_echo = 13,
  };
  const int mesures = 2;
  const int delayBetweenReads = 25;
  const int delayBetweenMesures = 100;
  
  SR04 sr04 = SR04(UltrasonicSensor_echo, UltrasonicSensor_trig);

  public:
  UltrasonicSensor();
  long ReadDistance();
  void DisplayDistance();
  void DisplayMesure();

  void Test();
};

#endif
