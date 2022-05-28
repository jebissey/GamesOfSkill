#include "Joystick.h"
#include "Time.h"

Joystick::Joystick()
{
  pinMode(joystick_button, INPUT);
  digitalWrite(joystick_button, HIGH);
}

void  Joystick::Check()
{
  int buttonState = digitalRead(joystick_button);
  if (buttonState != lastButtonState)
  { 
    lastButtonState = buttonState;
    debounceTime = millis();
    if(buttonState != buttonOff) clickTime = millis();
    buttonFallingEdge = (buttonState == buttonOff);
  }
  else if ((millis() - debounceTime) > debounceDelay)
  {
    if(buttonState != buttonOff)
    {
      if(millis() - clickTime > buttonPressedDelay) button = buttonPressed;
      else button = buttonOn;
    }
    else 
    {
      if(buttonFallingEdge) 
      {
        buttonFallingEdge = false;
        if(button != buttonPressed) buttonClicks++;        
      }
      button = buttonOff;
    }
  }
}

bool Joystick::IsClicked()   
{ 
  if(buttonClicks == 0) return false;
  return buttonClicks--; 
}
bool Joystick::IsPressed()   { return button == buttonPressed; }
bool Joystick::IsNeutralPosition(int position) { return abs(neutralPosition - position) < neutralPositionWidth; }
int Joystick::IsExtremePositionX() { return IsExtremePosition(analogRead(joystick_xAxe)); }
int Joystick::IsExtremePositionY() { return IsExtremePosition(analogRead(joystick_yAxe)); }
int Joystick::GetX() { return GetJoystickXY(analogRead(joystick_xAxe)); }
int Joystick::GetY() { return GetJoystickXY(analogRead(joystick_yAxe)); }

int Joystick::GetJoystickXY(int position)
{
  if(IsNeutralPosition(position)) return 0;
  if(position > neutralPosition) return map(position, xyMin, neutralPosition, xyMinSent, 0);;
  return map(position, neutralPosition, xyMax, 0, xyMaxSent);
}

int Joystick::IsExtremePosition(int position)
{
  if( xyMax - position < extremePositionWidth) return 1;
  if( position + xyMin < extremePositionWidth) return -1;
  return 0;
}


void Joystick::Test()
{
  static unsigned long aTime;
  static Time time;
  
  if(time.IsOver(500, &aTime))
  {
    Serial.print("x=");
    Serial.print(GetJoystickXY(analogRead(joystick_xAxe)));
    Serial.print(", xExt=");
    Serial.print(IsExtremePositionX());
    Serial.print("; y=");
    Serial.print(GetJoystickXY(analogRead(joystick_yAxe)));
    Serial.print(", yExt=");
    Serial.print(IsExtremePositionY());
    Serial.print("; clicks=");
    Serial.print(buttonClicks);
    Serial.print("; Button is clicked=");
    Serial.print(IsClicked());
    Serial.print("; Button is pressed=");
    Serial.println(IsPressed());
  }
}
