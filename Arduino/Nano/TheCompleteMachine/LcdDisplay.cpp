#include "LcdDisplay.h"

LcdDisplay::LcdDisplay()
{  
  pinMode(rs_pin, OUTPUT);
  pinMode(enable_pin, OUTPUT);
  lcd.begin(lcdColumns, lcdRaws);
  lcd.noDisplay();
}

void LcdDisplay::SwitchOff()
{
  if(time.NewTenSeconds(&tenSeconds, tenSeconds)) lcd.noDisplay();
}

void LcdDisplay::Write(String message, int column = 0, int raw = 0)
{
  lcd.display();
  lcd.setCursor(column, raw);
  lcd.print(message);
  time.NewTenSeconds(&tenSeconds, tenSeconds);
}


void LcdDisplay::Test()
{
  lcd.print("Hello, World!");
  lcd.setCursor(0, 1);
  lcd.print(millis()/1000);
} 
