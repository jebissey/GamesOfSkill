#ifndef LEDS_SQUARE_H
#define LEDS_SQUARE_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "MatriceLeds.h"
#include "RowCol.h"


enum SquareLight {On, Off}; 

class LedsSquare{
private:
  const int matriceSize = 8;
  MatriceLeds matriceLeds;
  RowCol squareSize;
  RowCol squareCoordonate;
  SquareLight squareLight;
  void SetSquare(bool stateLed);
  
public:
  LedsSquare(MatriceLeds matriceLeds_, RowCol squareSize_){
    matriceLeds = matriceLeds_; 
    squareSize = squareSize_;
  }
  
  void Move(RowCol squareCoordonate);
  void SetLight(SquareLight squareLight);
  void SetSize(RowCol squareSize);

  RowCol      GetCoordonate()  { return squareCoordonate;  }
  SquareLight GetLight()       { return squareLight;  }
  RowCol      GetSize()        { return squareSize;  }
};


#endif
