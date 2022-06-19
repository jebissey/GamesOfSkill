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
  MatriceLeds matriceLeds;
  RowCol squareSize;
  RowCol squareCoordonate;
  SquareLight squareLight;
  
  void SetSquare(bool stateLed){
    Serial.print(", stateLed=");
    Serial.print(stateLed);
    for(int row = squareCoordonate.row; row < squareCoordonate.row + squareSize.row; row++){
      for(int col = squareCoordonate.col; col < squareCoordonate.col + squareSize.col; col++){
        if(row >= 0 && row < matriceSize && col >= 0 && col < matriceSize){ 
          matriceLeds.SetLed(row, col, stateLed);
          Serial.print(", row=");
          Serial.print(row);
          Serial.print(", col=");
          Serial.print(col);
          Serial.print(". ");
        }
      }
    }
    Serial.println("___");
  }
  
public:
  const int matriceSize = 8;
  LedsSquare(MatriceLeds matriceLeds_, RowCol squareSize_){
    matriceLeds = matriceLeds_; 
    squareSize = squareSize_;
  }

  RowCol      GetCoordonate() { return squareCoordonate; }
  SquareLight GetLight()      { return squareLight; }
  RowCol      GetSize()       { return squareSize; }

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
    if(squareCoordonate.row > matriceSize - squareSize.row + 2) squareCoordonate.row = matriceSize - squareSize.row + 2;
    
    squareCoordonate.col += squareIncrement.col;
    if(squareCoordonate.col < -squareSize.col + 1) squareCoordonate.col = -squareSize.col + 1;
    if(squareCoordonate.col > matriceSize - squareSize.col + 1) squareCoordonate.col = matriceSize - squareSize.col + 1;
    
    if(squareLight == On) SetSquare(true);
  }
  
  void SetLight(SquareLight squareLight_){
    squareLight = squareLight_;
    SetSquare(squareLight == On);
  }
  
  void SetSize(RowCol squareSize_){
    if(squareLight == On) SetSquare(false);
    squareSize = squareSize_;
    if(squareLight == On) SetSquare(true);
  }
};

#endif
