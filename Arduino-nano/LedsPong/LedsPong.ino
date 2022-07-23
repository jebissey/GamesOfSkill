
#include "Time.h"
static Time time;

#include "Pong.h"
static Pong pong;

void setup() {
  pong.Setup();
  randomSeed(3);
  Serial.begin(9600);
}

void loop() { 
  pong.Run();

delay(50);
//Serial.print(".");

  static unsigned long temperatureTime;
  if(time.IsOver(1000, &temperatureTime)){
    Serial.println("");
  }
}
