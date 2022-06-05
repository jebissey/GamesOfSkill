
#include "LedsSquare.h"


  
void LedsSquare::Move(RowCol squareCoordonate_){
  if(squareLight == On) SetSquare(false);
  squareCoordonate = squareCoordonate_;
  if(squareLight == On) SetSquare(true);
}

void LedsSquare::SetLight(SquareLight squareLight_){
  squareLight = squareLight_;
  SetSquare(squareLight == On);
}

void LedsSquare::SetSize(RowCol squareSize_){
  if(squareLight == On) SetSquare(false);
  squareSize = squareSize_;
  if(squareLight == On) SetSquare(true);
}

void LedsSquare::SetSquare(bool stateLed){
  for(int row = squareCoordonate.row; row < squareCoordonate.row + squareSize.row; row++){
    for(int col = squareCoordonate.col; col < squareCoordonate.col + squareSize.col; col++){
      if(row >= 0 && row < matriceSize && col >= 0 && col < matriceSize) matriceLeds.SetLed(row, col, stateLed);
    }
  }
}
