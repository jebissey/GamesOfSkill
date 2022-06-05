#ifndef MATRICE_LED_H
#define MATRICE_LED_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#include <LedControl.h>
#include "AAA_PinsEnum.h"

class MatriceLeds : LedControl{
private:

public:
  static const int matriceSize = 8;
  MatriceLeds() : LedControl(leds_DataIn,leds_CLK,leds_CS){
    this->shutdown(0, false);
    this->setIntensity(0, 1);
    this->clearDisplay(0);
  }
  
  void SetLed(int row, int col, bool stateLed){  
    this->setLed(0, row, col, stateLed);
  }
  
  void SetColumn(int col, byte patern){  
    this->setColumn(0, col, patern);
  }
  
  void SetRow(int row, byte patern){  
    this->setRow(0, row, patern);
  }
};

#endif
