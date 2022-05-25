#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "PinsEnum.h"
#include "Time.h"
#include <LiquidCrystal.h> 

class LcdDisplay
{
  private:
  const int lcdColumns = 16;
  const int lcdRaws = 2;
  LiquidCrystal lcd = LiquidCrystal(rs_pin, enable_pin, d4_pin, d5_pin, d6_pin, d7_pin);

  unsigned long tenSeconds;
  Time time;
  
  public:
  LcdDisplay();
  void SwitchOff();
  void Write(String message, int column = 0, int raw = 0);
    
  void Test();
};

#endif
