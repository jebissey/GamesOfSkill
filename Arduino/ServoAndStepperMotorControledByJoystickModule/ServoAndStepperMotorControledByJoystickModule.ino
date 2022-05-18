void setup() 
{
 ServoSetup();
 JoystickSetup();
 StepperMotorSetup();
 UltrasonicSensorSetup();
 Serial.begin(9600);
}

void loop() 
{
  if(JoystickPressed())
  {
    if(ThrowMovement(70))
    {
      DisplayDistance();
    }
  }
  
  PulleyMove(GetJoystickX());

  if(IsExtremePositionY() > 0) GoUpOneStep();
  if(IsExtremePositionY() < 0) GoDownOneStep();
  
}


// ======================================================================
// Ultrasonic sensor
#include <SR04.h>
enum 
{
  UtrasonicSensor_trig = 12,
  UtrasonicSensor_echo = 13,
};
const int mesures = 5;
const int delayBetweenReads = 25;
const int delayBetweenMesures = 100;

SR04 sr04 = SR04(UtrasonicSensor_echo, UtrasonicSensor_trig);

void UltrasonicSensorSetup()
{
 //already done
}

long ReadDistance()
{
  long cumulDistance = 0;
  for(int i = 0; i <mesures; i++)
  {
    cumulDistance += sr04.Distance();
    delay(delayBetweenReads);    
  }
  return cumulDistance / mesures;
}

void DisplayDistance()
{
  long distance1, distance2;
  int mesures = 0;
  do {
    distance1 = ReadDistance();
    delay(delayBetweenMesures);
    distance2 = ReadDistance();
    delay(delayBetweenMesures);
    mesures++;
  } while(abs(distance1 - distance2) > 2);
  Serial.print(distance1);
  Serial.print(" (");
  Serial.print(mesures);
  Serial.println(") cm");
}
// ======================================================================
// Pulley with stepper motor

#include <Stepper.h> 
const int stepperMotorSteps = 2048;
const int rotationalIncrement = stepperMotorSteps / 128;
enum 
{
  stepperMotor_in1 = 8,
  stepperMotor_in2 = 9,
  stepperMotor_in3 = 10,
  stepperMotor_in4 = 11,
};
const int speed = 16; // [1 .. 16]

Stepper pulley(stepperMotorSteps, stepperMotor_in1, stepperMotor_in3, stepperMotor_in2, stepperMotor_in4);

void StepperMotorSetup()
{
 pulley.setSpeed(speed);
}

void PulleyMove(int steps)
{
  if(steps != 0) pulley.step(steps);
}


// ======================================================================
// Joystick
enum
{
  joystick_xAxe = 0,
  joystick_yAxe = 1,
  joystick_button = 2,
};
const int xyMin = 0;
const int xyMax = 1020;
const int neutralPosition = (xyMax - xyMin) / 2;
const int neutralPositionWidth = 150;
const int extremePositionWidth = 150;

void JoystickSetup()
{
  pinMode(joystick_button, INPUT);
  digitalWrite(joystick_button, HIGH);
}

bool IsNeutralPosition(int position) { return abs(neutralPosition - position) < neutralPositionWidth; }
bool JoystickPressed()   { return digitalRead(joystick_button) == 0; }
int IsExtremePositionX() { return IsExtremePosition(analogRead(joystick_xAxe)); }
int IsExtremePositionY() { return IsExtremePosition(analogRead(joystick_yAxe)); }
int GetJoystickX()       { return GetJoystickXY(analogRead(joystick_xAxe)); }
int GetJoystickY()       { return GetJoystickXY(analogRead(joystick_yAxe)); }

int GetJoystickXY(int position)
{
  if(IsNeutralPosition(position)) return 0;
  if(position > neutralPosition) return -rotationalIncrement;
  return rotationalIncrement;
}

int IsExtremePosition(int position)
{
  if( xyMax - position < extremePositionWidth) return 1;
  if( position + xyMin < extremePositionWidth) return -1;
  return 0;
}

// ======================================================================
// Catapult with servo motor

#include <Servo.h>

enum { servoMotor_pin = 7};
const int startPosition = 0;
const int endPosition = 110;
const int catchPosition = 60;
const int increment = 1;
const int delayBetweenPositionChange = 20;
const int delayBeforeReturn = 500;

Servo servoCatapult;

void ServoSetup()
{
  servoCatapult.attach(servoMotor_pin);
  SetServoPosition(startPosition);
}

bool ThrowMovement(int position)
{
  if(servoCatapult.read() > startPosition)
  {
     ReturnMovement(delayBetweenPositionChange, startPosition);
     return false;
  }
  SetServoPosition(position);
  delay(delayBeforeReturn);
  ReturnMovement(delayBetweenPositionChange, catchPosition);
  return true;
}

void ReturnMovement(int speed, int position)
{
  while (servoCatapult.read() > position) GoOneStep(speed, -increment);
  SetServoPosition(position);
}

void CatchTheBall()  { SetServoPosition(catchPosition); }
void GoDownOneStep() { GoOneStep(delayBetweenPositionChange * 20, -increment); }
void GoUpOneStep()   { GoOneStep(delayBetweenPositionChange * 20, increment); }

void GoOneStep(int delayInMilisecond, int increment)
{
  int pos = servoCatapult.read();
  SetServoPosition(pos + increment);  
  delay(delayInMilisecond);
}

void SetServoPosition(int position)
{
  if(position >= startPosition && position <= endPosition) servoCatapult.write(position); 
}
// ======================================================================
