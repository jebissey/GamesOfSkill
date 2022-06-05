#ifndef PINS_ENUM_H
#define PINS_ENUM_H

enum Free{
  free0 = 0,                // D0 / RX
  free1 = 1,                // D1 / TX
  //free2 = 2,                // D2
  //free3 = 3,                // D3
  //free4 = 4,                // D4
  free5 = 5,                // D5
  free6 = 6,                // D6
  free7 = 7,                // D7
  free8 = 8,                // D8
  free9 = 9,                // D9
  free10 = 10,              // D10
  free11 = 11,              // D11
  free12 = 12,              // D12
  //free13 = 13,              // D13       / SCK
  free14 = 14,              // D14 / A0
  free15 = 15,              // D15 / A1
  free16 = 16,              // D16 / A2
  free17 = 17,              // D17 / A3
  //free18 = 18,              // D18 / A4 / SCL
  //free19 = 19,              // D19 / A5 / SDA
  freeA6 = 0xA6,            //     / A6
  freeA7 = 0xA7,            //     / A7
};

enum Leds8x8{
  leds_CLK = 2,
  leds_CS = 3,
  leds_DataIn = 4,
};

enum Gy521{
  Gy_SCL = 18,
  Gy_SDA = 19,
};
#endif
