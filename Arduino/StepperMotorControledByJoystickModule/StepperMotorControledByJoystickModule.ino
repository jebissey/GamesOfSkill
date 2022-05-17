#include <Stepper.h> 
double Pas = 2048;
Stepper moteur(Pas, 8, 10, 9, 11);  // Attention a l'ordre des pins

void setup() { 
 moteur.setSpeed(16);  
 Serial.begin(9600); 
 } 
 
 void loop() {  
 
   Serial.println("sens des aiguilles d'une montre");    
   moteur.step(Pas);  
   delay(100); 
    
   Serial.println("Sens inverse des aiguilles d'une montre");  
   moteur.step(-Pas); 
   delay(1000); 
 }
