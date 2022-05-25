#ifndef PHOTOCELL_H
#define PHOTOCELL_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "AAA_PinsEnum.h"

class PhotoCell
{
  private:

  
  public:
  PhotoCell();
  int Get();
  
  void Test();
};

#endif
