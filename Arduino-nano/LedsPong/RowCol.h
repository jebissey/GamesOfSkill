#ifndef ROW_COL_H
#define ROW_COL_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


struct RowCol
{
private:

public:
  int row;
  int col;
  
  RowCol(){
  }
  
  RowCol(int row_, int col_){
    row = row_; 
    col = col_;
  }
};


#endif
