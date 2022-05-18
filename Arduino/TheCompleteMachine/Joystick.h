#ifndef JOYSTICK_H
#define JOYSTICK_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class Joystick
{
  private:
  enum
  {
    joystick_xAxe = 0,
    joystick_yAxe = 1,
    joystick_button = 2,
  };
  const int xyMin = 0;
  const int xyMax = 1020;
  const int neutralPosition = (xyMax - xyMin) / 2;
  const int neutralPositionWidth = 150;
  const int extremePositionWidth = 150;
  
  int GetJoystickXY(int position);
  int IsExtremePosition(int position);
  bool IsNeutralPosition(int position);
  
  public:
  Joystick();
  bool JoystickPressed();
  int IsExtremePositionX();
  int IsExtremePositionY();
  int GetX();
  int GetY();
  
  void Test();
};

#endif