#ifndef PINS_ENUM_H
#define PINS_ENUM_H

enum
{
  free0 = 0,                // D0 / RX
  free1 = 1,                // D1 / TX
  built_in_led = 13,        // D13
  free16 = 16,         // A5 | D16
  free17 = 17,         // A3 | D17
  free18 = 18,         // A4 | D18
};

enum
{
  photoCell_basket = 19,//A5
};
enum 
{ 
  servoMotor_pin = 3,       //D3
}; 
enum
{
  joystick_xAxe = 6,   //A6
  joystick_yAxe = 7,   //A7
  joystick_button = 2,      //D2
};
enum 
{
  lcd_rs_pin = 14,          //D14
  lcd_enable_pin = 15,      //D15
  lcd_d4_pin = 13,          //D13
  lcd_d5_pin = 12,          //D12
  lcd_d6_pin = 11,          //D11
  lcd_d7_pin = 10,          //D10
};
enum 
{
  stepperMotor_in1 = 6,     //D6
  stepperMotor_in2 = 7,     //D7
  stepperMotor_in3 = 8,     //D8
  stepperMotor_in4 = 9,     //D9
};
enum 
{
  UltrasonicSensor_trig = 4,//D4
  UltrasonicSensor_echo = 5,//D5
}; 
#endif
