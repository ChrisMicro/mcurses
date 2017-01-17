/*-----------------------------------------------------------------------------------------------------------------

   draw a circle 

   Revision History:
   V1.0 2017 01 17 ChrisMicro, initial version

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

  ---------------------------------------------------------------------------------------------------------------*/

#include "mcurses.h"

#define VT100_moveTo(x,y) move(y,x)

void Arduino_putchar(uint8_t c)
{
  Serial.write(c);
}

void setup() 
{
  Serial.begin(115200);

  setFunction_putchar(Arduino_putchar); // tell the library which output channel shall be used

  initscr();                  // initialize mcurses

  Serial.print("VT100 graphics demo");
  delay(3000);
  clear();
}

#define POINTS 100

#define YPOS 20
#define XPOS 20
#define RADIUS 15
#define SCALEX 2.3

void loop() 
{
  static float n=0;
  float x,y;
  
  x=(sin(2*PI*n/POINTS)*RADIUS+XPOS)*SCALEX;
  y=cos(2*PI*n/POINTS)*RADIUS+YPOS;
  n++;
  VT100_moveTo(x,y);
  Serial.print("+");

  delay(100);
}

