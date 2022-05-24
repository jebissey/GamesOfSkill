#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

#include <SR04.h>

class UltrasonicSensor
{
  private:
  enum 
  {
    UltrasonicSensor_trig = 4,
    UltrasonicSensor_echo = 5,
  }; 
  SR04 sr04 = SR04(UltrasonicSensor_echo, UltrasonicSensor_trig);

  public:
  UltrasonicSensor();
  long ReadDistance();

  void Test();
};

#endif
