

#include "Pong.h"
Pong pong;

  
void setup() {
  pong.Setup();
  
  Serial.begin(9600);
}


void loop() { 

  pong.MoveTheBall();

  
}
