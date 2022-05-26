#include "LcdDisplay.h"

LcdDisplay::LcdDisplay()
{  
  pinMode(lcd_rs_pin, OUTPUT);
  pinMode(lcd_enable_pin, OUTPUT);
  pinMode(lcd_d4_pin, OUTPUT);
  pinMode(lcd_d5_pin, OUTPUT);
  pinMode(lcd_d6_pin, OUTPUT);
  pinMode(lcd_d7_pin, OUTPUT);
  lcd.begin(lcdColumns, lcdRaws);
  lcd.noDisplay();
}

void LcdDisplay::SwitchOff()
{
  if(time.Delay(&aTime, aTime, switchOffDelay)) lcd.noDisplay();
}

void LcdDisplay::Write(String message, int column = 0, int raw = 0)
{
  lcd.display();
  lcd.setCursor(column, raw);
  lcd.print(message);
  time.Reset(&aTime);
}


void LcdDisplay::Test()
{
  lcd.print("Hello, World!");
  lcd.setCursor(0, 1);
  lcd.print(millis()/1000);
} 
