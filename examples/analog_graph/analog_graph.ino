/*-----------------------------------------------------------------------------------------------------------------

   show analog input 0 as graph in a text box

   Revision History:
   V1.0 2017 01 17 ChrisMicro, initial version

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

  ---------------------------------------------------------------------------------------------------------------*/

#include "mcurses.h"

#define VT100_moveTo(x,y) move(y,x)
#define MAXX 80
#define MAXY 25
#define MINX 2

void drawFrame()
{
  int n;
  for (n = 0; n < MAXX + 1; n++)
  {
    VT100_moveTo(n, 0); Serial.print("-");
    VT100_moveTo(n, MAXY + 1); Serial.print("-");
  }
  for (n = 0; n < MAXY + 1; n++)
  {
    VT100_moveTo(0, n); Serial.print("|");
    VT100_moveTo(MAXX + 1, n); Serial.print("|");
  }
}

void Arduino_putchar(uint8_t c)
{
  Serial.write(c);
}

void setup()
{
  Serial.begin(115200);

  Serial.println("show analog input A0 as graph");
  delay(2000);
  for (int n = 0; n < 50; n++)Serial.println("");

  setFunction_putchar(Arduino_putchar); // tell the library which output channel shall be used

  initscr();                  // initialize mcurses

  drawFrame();
}

int xpos = MINX;

void loop()
{
  int value = analogRead(A0);
  VT100_moveTo(40, 0);
  Serial.print(" ADC0: "); Serial.print(value); Serial.print("   ");

  // map(long x, long in_min, long in_max, long out_min, long out_max)
  int v2 = map(value, 0, 1023, 0, MAXY * 2 - 2);
  VT100_moveTo(xpos++, MAXY - v2 / 2);
  if (v2 & 1)  Serial.print('-');
  else Serial.print('_');

  if (xpos > MAXX)
  {
    delay(1000);
    clear();
    drawFrame();
    xpos = MINX;
  }

}

