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


SettingMode::SettingMode()
{  
  State stateStart(&OnStart, NULL, NULL);
  State stateStartSettingPulley(&OnStartSettingPulley, NULL, NULL);
  State stateMoveUp(&OnMoveUp, NULL, NULL);
  State stateMoveDown(&OnMoveDow, NULL, NULL);
  State stateMoveTop(&OnMoveTop, NULL, NULL);
  State stateStop(&OnStop, NULL, NULL);

/*
  Fsm fsm(&stateStart);

  fsm.add_transition(&stateStart, &StartSettingPulley, joystick.IsPressed(), NULL);
  fsm.add_transition(&stateStart, &MoveUp, !joystick.IsClickeded(), NULL);
  fsm.add_transition(&MoveUp, &MoveDown, joystick.IsClickeded(), NULL);
  fsm.add_transition(&MoveDown, &MoveTop, joystick.IsClickeded(), NULL);
  fsm.add_transition(&MoveTop, &MoveUp, joystick.IsClickeded(), NULL);
  fsm.add_transition(&MoveTop, &Stop, joystick.IsPressed(), NULL);

  this-r>un_machine();*/
}
