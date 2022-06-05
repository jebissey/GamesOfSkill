
#include "Time.h"
static Time time;


#include "Pong.h"
static Pong pong;


void setup() {
  pong.Setup();
  
  Serial.begin(9600);
}


void loop() { 
  pong.MoveTheBall();

  static unsigned long temperatureTime;
  if(time.IsOver(1000, &temperatureTime)){
    Serial.print("temperature=");
    Serial.println(pong.GetTemperature());
  }
  
}
