#ifndef GY_521_H
#define GY_521_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include<Wire.h>

class Gy_521{
private:
  static const int numData = 7;
  static const int I2C_AddrOfMPU=0x68;
  static const int indexForTemperature = 3;
  static int datum[numData];
  
  void ReadGY521(){
    Wire.beginTransmission(I2C_AddrOfMPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(I2C_AddrOfMPU, numData * 2, true);

    for(int i=0; i<numData; i++){
      datum[i] = Wire.read()<<8 | Wire.read();
      if(i==indexForTemperature) temperature = datum[i] / 340.0 + 36.53; 
    }
  }

  void ComputeAngle(float boardTilts[]){
    float x = datum[0];
    float y = datum[1];
    float z = datum[2];
    boardTilts[0] = (atan(x/sqrt((y*y) + (z*z)))) *  180.0 / PI;
    boardTilts[1] = (atan(y/sqrt((x*x) + (z*z)))) *  180.0 / PI;
    boardTilts[2] = (atan(z/sqrt((x*x) + (y*y)))) *  180.0 / PI;
  }

public:
  static float temperature;

  void Setup(){
    Wire.begin();
    Wire.beginTransmission(I2C_AddrOfMPU);
    Wire.write(0x6B); 
    Wire.write(0);    
    Wire.endTransmission(true);
  }

  void Read(float boardTilts[]){
    ReadGY521();
    ComputeAngle(boardTilts);
  }

  bool IsShaked(){ 
    ReadGY521();
    return abs(datum[4]) + abs(datum[5]) + abs(datum[6]) > 22500; 
  }
};

float Gy_521::temperature = 0;
int Gy_521::datum[numData];

#endif
