#ifndef OPERATING_MODE_H
#define OPERATING_MODE_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Joystick.h"


class OperatingMode
{
  private:
  int mode = manual;
  Joystick joystick;
  
  public:
  OperatingMode();
  int Get();
  void Set(int modeToSet);

  enum {test, manual, setting};
};

#endif
