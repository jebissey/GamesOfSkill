#ifndef LEDS_SQUARE_H
#define LEDS_SQUARE_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "RowCol.h"

#include <LedControl.h>
#include "AAA_PinsEnum.h"


class LedsSquare : public LedControl{
private:
  enum SquareLight {On, Off}; 
  RowCol squareSize;
  RowCol squareCoordonate;
  SquareLight squareLight;
  
  void SetSquare(bool stateLed){
    for(int row = squareCoordonate.row; row < squareCoordonate.row + squareSize.row; row++){
      for(int col = squareCoordonate.col; col < squareCoordonate.col + squareSize.col; col++){
        if(row >= 0 && row < matrixSize && col >= 0 && col < matrixSize){ 
          this->setLed(0, row, col, stateLed);
        }
      }
    }
  }
    
  void SetLight(SquareLight squareLight_){
    squareLight = squareLight_;
    SetSquare(squareLight == On);
  }
  
public:
  static const int matrixSize = 8;
  LedsSquare(RowCol squareSize_) : LedControl(leds_DataIn, leds_CLK, leds_CS, 1){
    squareSize = squareSize_;
    
    this->shutdown(0, false);
    this->setIntensity(0, 1);
    this->clearDisplay(0);
  }

  RowCol GetCoordonate() { return squareCoordonate; }
  RowCol GetSize()       { return squareSize; }
  void   SetLightOn()    { SetLight(On); }
  void   SetLightOff()   { SetLight(Off); }
  bool   IsLightOff()    { return squareLight == Off; }

  void MoveAbsolute(RowCol squareCoordonate_){
    if(squareLight == On) SetSquare(false);
    squareCoordonate = squareCoordonate_;
    if(squareLight == On) SetSquare(true);
  }

  void MoveRelative(RowCol squareIncrement){
    if(squareIncrement.row == 0 && squareIncrement.col == 0) return;
     
    if(squareLight == On) SetSquare(false);
    
    squareCoordonate.row += squareIncrement.row;
    if(squareCoordonate.row < -squareSize.row + 1) squareCoordonate.row = -squareSize.row + 1;
    if(squareCoordonate.row > matrixSize - squareSize.row + 1) squareCoordonate.row = matrixSize - squareSize.row + 1;
    
    squareCoordonate.col += squareIncrement.col;
    if(squareCoordonate.col < -squareSize.col + 1) squareCoordonate.col = -squareSize.col + 1;
    if(squareCoordonate.col > matrixSize - squareSize.col + 1) squareCoordonate.col = matrixSize - squareSize.col + 1;
    
    if(squareLight == On) SetSquare(true);
  }
  
  void SetSize(RowCol squareSize_){
    if(squareLight == On) SetSquare(false);
    squareSize = squareSize_;
    if(squareLight == On) SetSquare(true);
  }

  void ClearDisplay() { this->clearDisplay(0);}

  void DisplayPoints(int points){
    for(int row = 0; row < matrixSize; row++){
      for(int col = 0; col < matrixSize; col++){
        if(row >= 0 && row < matrixSize && col >= 0 && col < matrixSize){ 
          if(points-- <=0) return;
          this->setLed(0, row, col, true);
        }
      }
    }
  }
};

#endif
