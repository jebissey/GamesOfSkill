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
  PhotoCell(){
    pinMode(photoCell_basket, INPUT);
  }
  
  int Get() {
    return  analogRead(photoCell_basket);
  }
  
    
  void Test(){
    Serial.print("photo cell=");
    Serial.print(Get());
    delay(500);
  }
};

#endif
