#include "Joystick.h"

Joystick::Joystick()
{
  pinMode(joystick_button, INPUT);
  digitalWrite(joystick_button, HIGH);
}

void  Joystick::Check()
{
  int reading = digitalRead(joystick_button);
  if (reading != lastButtonState)
  {
    lastButtonState = reading;
    lastDebounceTime = millis();
    if(reading != buttonOff) lastClickTime = millis();
  }
  else if ((millis() - lastDebounceTime) > debounceDelay)
  {
    if(reading != buttonOff)
    {
      if ((millis() - lastClickTime) > buttonPressedDelay) button = buttonPressed;
      else button = buttonClicked;
    }
    else button = buttonOff;
  }
}

bool Joystick::IsNeutralPosition(int position) { return abs(neutralPosition - position) < neutralPositionWidth; }
bool Joystick::IsClicked()   { return button == buttonClicked; }
bool Joystick::IsPressed()   { return button == buttonPressed; }
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
  Serial.print("x=");
  Serial.print(GetJoystickXY(analogRead(joystick_xAxe)));
  Serial.print(", xExt=");
  Serial.print(IsExtremePositionX());
  Serial.print("; y=");
  Serial.print(GetJoystickXY(analogRead(joystick_yAxe)));
  Serial.print(", yExt=");
  Serial.print(IsExtremePositionY());
  Serial.print("; Button=");
  Serial.println(IsPressed());
  delay(500);
}
