#include "OperatingMode.h"

OperatingMode::OperatingMode()
{  
  
}


int OperatingMode::Get()
{
  return mode;
}

void OperatingMode::Set(int modeToSet)
{
  mode = modeToSet;
}
