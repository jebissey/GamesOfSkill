
#include<Wire.h>
const int MPU=0x68; 
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

#include "MatriceLeds.h"
MatriceLeds matriceLeds;

#include "LedsSquare.h"
RowCol sizeSquare = RowCol(2, 2);
LedsSquare ledsSquare = LedsSquare(matriceLeds, sizeSquare);

/* we always wait a bit between updates of the display */
unsigned long delaytime1=500;
unsigned long delaytime2=50;
void setup() {


  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  
  Serial.begin(9600);
}







void loop() { 



  matriceLeds.SetColumn(0, B11111111);
  matriceLeds.SetColumn(7, B11111111);
  delay(500);
  matriceLeds.SetColumn(0, B00000000);
  matriceLeds.SetColumn(7, B00000000);
  
  matriceLeds.SetRow(0, B11111111);
  matriceLeds.SetRow(7, B11111111);
  delay(500);


  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read();  
  GyX=Wire.read()<<8|Wire.read();  
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read();  
  
  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(AcX);
  Serial.print(" | Y = "); Serial.print(AcY);
  Serial.print(" | Z = "); Serial.println(AcZ); 
  
  Serial.print("Gyroscope: ");
  Serial.print("X = "); Serial.print(GyX);
  Serial.print(" | Y = "); Serial.print(GyY);
  Serial.print(" | Z = "); Serial.println(GyZ);
  Serial.println(" ");
  delay(333);
  
}
