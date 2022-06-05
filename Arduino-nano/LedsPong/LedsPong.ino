

#include "MatriceLeds.h"
static MatriceLeds matriceLeds;


#include "LedsSquare.h"
RowCol squareSize = RowCol(2, 2);
LedsSquare ledsSquare = LedsSquare(matriceLeds, squareSize);


#include "Gy521.h"
static Gy_521 gy521;

void setup() {
  gy521.Setup();
  ledsSquare.MoveAbsolute(RowCol(3, 3));
  
  Serial.begin(9600);
}


void MoveSquare(unsigned long delayOnOf){
  for(int row = 0; row < matriceLeds.matriceSize; row++){
    for(int col = 0; col < matriceLeds.matriceSize; col++){
      ledsSquare.MoveAbsolute(RowCol(row, col));
      delay(delayOnOf);
    }
  }
}



int ledsSquareSize = 0;
int  GyAccTemp[gy521.numData];
float PitchRoll[3];

void loop() { 

/*

  matriceLeds.SetColumn(0, B11111111);
  matriceLeds.SetColumn(7, B11111111);
  delay(250);
  matriceLeds.SetColumn(0, B00000000);
  matriceLeds.SetColumn(7, B00000000);
  
  matriceLeds.SetRow(0, B11111111);
  matriceLeds.SetRow(7, B11111111);
  delay(250);

  ledsSquareSize = ((ledsSquareSize++) % matriceLeds.matriceSize) + 1;
  ledsSquare.SetSize(RowCol(ledsSquareSize, ledsSquareSize));
  MoveSquare(25);
*/
  





  gy521.ReadGY521(GyAccTemp);
  gy521.ComputeAngle(GyAccTemp,PitchRoll);
  int ballRowIncrement = round(map(PitchRoll[1], -90, +90, -10, +10) / 3.0);
  int ballColIncrement = round(map(PitchRoll[2], -90, +90, +10, -10) / 3.0);
  ledsSquare.MoveRelative(RowCol(ballRowIncrement, ballColIncrement));


  delay(100);
  
}
