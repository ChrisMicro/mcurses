/*---------------------------------------------------------------------------------------------------------------------------------------------------
   mcurses box demo

   Copyright (c) 2011-2015 Frank Meyer - frank(at)fli4l.de

   Revision History:
   V1.0 2015 xx xx Frank Meyer, original version
   V1.1 2017 01 14 ChrisMicro, converted to Arduino example

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
  ---------------------------------------------------------------------------------------------------------------------------------------------------
*/
#include "mcurses.h"

#define         myitoa(x,buf)                   itoa ((x), buf, 10)

void drawbox (uint8_t y, uint8_t x, uint8_t h, uint8_t w)
{
  uint8_t line;
  uint8_t col;

  move (y, x);
  addch (ACS_ULCORNER);
  for (col = 0; col < w - 2; col++)
  {
    addch (ACS_HLINE);
  }
  addch (ACS_URCORNER);

  for (line = 0; line < h - 2; line++)
  {
    move (line + y + 1, x);
    addch (ACS_VLINE);
    move (line + y + 1, x + w - 1);
    addch (ACS_VLINE);
  }

  move (y + h - 1, x);
  addch (ACS_LLCORNER);
  for (col = 0; col < w - 2; col++)
  {
    addch (ACS_HLINE);
  }
  addch (ACS_LRCORNER);
}


void Arduino_putchar(uint8_t c)
{
  Serial.write(c);
}

void setup()
{
  Serial.begin(115200);

  setFunction_putchar(Arduino_putchar); // tell the library which output channel shall be used

  initscr();                  // initialize mcurses

}

void loop()
{
  char    buf[10];
  uint8_t idx;
  clear ();
  drawbox (6, 20, 10, 20);

  for (idx = 1; idx <= 6; idx++)
  {
    mvaddstr_P (idx + 7, 23, PSTR("This is line "));
    addstr (myitoa(idx, buf));
    delay (400);
  }
  delay (1000);
  clear ();
}
