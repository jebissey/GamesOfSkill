#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "AAA_PinsEnum.h"
#include "Time.h"
#include <LiquidCrystal.h> 

class LcdDisplay
{
  private:
  const int lcdColumns = 16;
  const int lcdRaws = 2;
  LiquidCrystal lcd = LiquidCrystal(lcd_rs_pin, lcd_enable_pin, lcd_d4_pin, lcd_d5_pin, lcd_d6_pin, lcd_d7_pin);

  const int switchOffDelay = 20*1000;
  unsigned long aTime;
  Time time;
  
  public:
  LcdDisplay();
  void SwitchOff();
  void Write(String message, int column = 0, int raw = 0);
    
  void Test();
};

#endif
