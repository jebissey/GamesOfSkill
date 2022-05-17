


void setup() 
{
 ServoSetup();
 JoystickSetup();
 StepperMotorSetup();
 Serial.begin(9600);
}

void loop() 
{
  if(JoystickPressed())
  {
    Throw (90);
    delay(500);
    Return();
  }
  PulleyMove(); 
}


// ======================================================================
// Stepper motor

#include <Stepper.h> 
const int stepperMotorSteps = 2048;
const int rotationalIncrement = stepperMotorSteps / 128;
const int in1 = 8;
const int in2 = 9;
const int in3 = 10;
const int in4 = 11;
const int speed = 16; // [1 .. 16]

Stepper pulley(stepperMotorSteps, in1, in3, in2, in4);

void StepperMotorSetup()
{
 //Stepper pulley = Stepper(stepperMotorSteps, in1, in3, in2, in4);
 pulley.setSpeed(speed);
}

void PulleyMove()
{
  int steps = GetJoystickX();
  if(steps != 0)
  {
    pulley.step(steps);
  }
}


// ======================================================================
// Joystick
const int xAxe = 0;
const int yAxe = 1;
const int buttonPressed = 2;

const int xyMin = 0;
const int xyMax = 1020;
const int neutralPosition = (xyMax - xyMin) / 2;
const int neutralPositionWidth = 120;

void JoystickSetup()
{
  pinMode(buttonPressed, INPUT);
  digitalWrite(buttonPressed, HIGH);
}

int GetJoystickX()
{
  return GetJoystickXY(analogRead(xAxe));
}


int GetJoystickY()
{
  return GetJoystickXY(analogRead(yAxe));
}

int GetJoystickXY(int position)
{
  if(IsNeutralPosition(position)) return 0;
  if(position > neutralPosition)
  {
    return rotationalIncrement;
  }
  return -rotationalIncrement;
}

bool JoystickPressed()
{
  return digitalRead(buttonPressed) == 0;
}

bool IsNeutralPosition(int position)
{
  return abs(neutralPosition - position) < neutralPositionWidth;
}

// ======================================================================
// Catapult

#include <Servo.h>
const int servoPin = 7;
const int startPosition = 0;
const int endPosition = 110;
const int increment = 5;
const int delayBetweenPositionChange = 25;

Servo catapult;

void ServoSetup()
{
  catapult.attach(servoPin);
  SetServoPosition(startPosition);
}

void Throw(int lastPosition)
{
  SetServoPosition(lastPosition);
}

void Return()
{
  int pos = catapult.read();
  for (pos; pos > startPosition; pos -= increment) 
  {
    SetServoPosition(pos);  
    delay(delayBetweenPositionChange);
  }
}
  
void SetServoPosition(int position)
{
  if(position >= startPosition && position <= endPosition)
  {
    catapult.write(position); 
  }
}
// ======================================================================
