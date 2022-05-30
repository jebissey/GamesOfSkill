#ifndef SETTING_MODE_H
#define SETTING_MODE_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Fsm.h>

#include "Joystick.h"


class SettingMode 
{
  private:
  enum Event {joystickButtonIsPressed, joystickButtonClicked, joystickButtonOff};
  Joystick joystick;
  Fsm fsm;
  
  void CheckJoystickButton();
  void OnStart();
  
  State start;
  

  
  public:
  SettingMode();

};

#endif
