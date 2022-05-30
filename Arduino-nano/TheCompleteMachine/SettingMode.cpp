#include "SettingMode.h"


void OnStart()
{
  
}

void OnStartSettingPulley()
{
  
}

void OnMoveUp()
{
  
}

void OnMoveDow()
{
  
}

void OnMoveTop()
{
  
}

void OnStop()
{
  
}

void SettingMode::CheckJoystickButton()
{
  /*if (joystick.IsClicked()) fsm.trigger(joystickButtonClicked);
  if (joystick.IsPressed()) fsm.trigger(joystickButtonIsPressed);
  fsm.trigger(joystickButtonOff);*/
}

SettingMode::SettingMode() : 
  State start(&OnStart, &CheckJoystickButton, NULL),
  fsm(&start)
{  
  
  State startSettingPulley(&OnStartSettingPulley, &CheckJoystickButton, NULL);
  State soveUp(&OnMoveUp, &CheckJoystickButton, NULL);
  State soveDown(&OnMoveDow, &CheckJoystickButton, NULL);
  State soveTop(&OnMoveTop, &CheckJoystickButton, NULL);
  State stop(&OnStop, &CheckJoystickButton, NULL);


  
  


  fsm.add_transition(&stateStart, &StartSettingPulley, joystick.IsPressed(), NULL);
  fsm.add_transition(&stateStart, &MoveUp, !joystick.IsClickeded(), NULL);
  fsm.add_transition(&MoveUp, &MoveDown, joystick.IsClickeded(), NULL);
  fsm.add_transition(&MoveDown, &MoveTop, joystick.IsClickeded(), NULL);
  fsm.add_transition(&MoveTop, &MoveUp, joystick.IsClickeded(), NULL);
  fsm.add_transition(&MoveTop, &Stop, joystick.IsPressed(), NULL);

  this-r>un_machine();
}
