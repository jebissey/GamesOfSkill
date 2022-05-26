#include "PhotoCell.h"

PhotoCell::PhotoCell()
{
  pinMode(photoCell_basket, INPUT);
}

int PhotoCell::Get()
{
  return  analogRead(photoCell_basket);
}




void PhotoCell::Test()
{
  Serial.print("photo cell=");
  Serial.print(Get());
  delay(500);
}
