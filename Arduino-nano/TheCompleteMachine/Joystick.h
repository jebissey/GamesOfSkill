#ifndef JOYSTICK_H
#define JOYSTICK_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "AAA_PinsEnum.h"

class Joystick
{
  private:
  const int xyMin = 0;
  const int xyMax = 1020;
  const int neutralPosition = (xyMax - xyMin) / 2;
  const int neutralPositionWidth = 150;
  const int extremePositionWidth = 200;
  
  const unsigned long debounceDelay = 10;
  unsigned long debounceTime = 0;
  const unsigned long buttonPressedDelay = 2000;
  unsigned long clickTime = 0;
  int buttonClicks = 0;
  enum 
  {
    buttonOn = 0,
    buttonOff = 1,
    buttonPressed,
  };
  int buttonState;  
  int lastButtonState = buttonOff; 
  int button = buttonOff;
  bool buttonFallingEdge;
  
  int GetJoystickXY(int position);
  int IsExtremePosition(int position);
  bool IsNeutralPosition(int position);
  
  public:
  const int xyMinSent = -100;
  const int xyMaxSent = 100;
  Joystick();
  void Check();
  bool IsClicked();
  bool IsPressed();
  int IsExtremePositionX();
  int IsExtremePositionY();
  int GetX();
  int GetY();
  
  void Test();
};

#endif
