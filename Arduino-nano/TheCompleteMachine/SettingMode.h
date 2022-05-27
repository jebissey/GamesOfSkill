#ifndef SETTING_MODE_H
#define SETTING_MODE_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Fsm.h>




class SettingMode
{
  private:
  enum State {Start, StartSettingPulley, MoveUp, MoveDown, Movetop, Stop};



  
  public:
  SettingMode();

};

#endif
