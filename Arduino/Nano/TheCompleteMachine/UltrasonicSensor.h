#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

#include "AAA_PinsEnum.h"
#include <SR04.h>

class UltrasonicSensor
{
  private:
  SR04 sr04 = SR04(UltrasonicSensor_echo, UltrasonicSensor_trig);

  public:
  UltrasonicSensor();
  long ReadDistance();

  void Test();
};

#endif
