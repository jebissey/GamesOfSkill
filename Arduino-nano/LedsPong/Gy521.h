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
  static const int MPU=0x68;
  double PitchRoll[3];

public:
  static const int numData = 7;
  int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

  void Setup(){
    Wire.begin();
    Wire.beginTransmission(MPU);
    Wire.write(0x6B); 
    Wire.write(0);    
    Wire.endTransmission(true);
  }

  void ReadGY521( int *GyAccTempp){
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 14, true);
  
    // Lecture des données (3 axes accélérometre + température + 3 axes gyroscope
    for(int i=0 ; i<numData ; i++){
      if(i!=3) GyAccTempp[i]=(Wire.read()<<8|Wire.read());
      else
      {
        GyAccTempp[i]=(Wire.read()<<8|Wire.read());
        GyAccTempp[i] = GyAccTempp[i]/340 + 36.53;
      }
    }
  }

  void ComputeAngle(int *GyAccTempp,  float *PitchRol){
    float x = GyAccTempp[0];
    float y = GyAccTempp[1];
    float z = GyAccTempp[2];
  
    PitchRol[0] = (atan(x/sqrt((y*y) + (z*z)))) *  180.0 / PI;
    PitchRol[1] = (atan(y/sqrt((x*x) + (z*z)))) *  180.0 / PI;
    PitchRol[2] = (atan(z/sqrt((x*x) + (y*y)))) *  180.0 / PI;
  }
};

#endif
