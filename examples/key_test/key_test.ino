/*---------------------------------------------------------------------------------------------------------------------------------------------------
   mcurses key test

   Copyright (c) 2011-2015 Frank Meyer - frank(at)fli4l.de

   Revision History:
   V1.0 2015 xx xx Frank Meyer, original version
   V1.1 2017 01 14 ChrisMicro, addapted as Arduino example

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
  ---------------------------------------------------------------------------------------------------------------------------------------------------
*/
#include "mcurses.h"

#define         myitoa(x,buf)                   itoa ((x), buf, 10)

void Arduino_putchar(uint8_t c)
{
  Serial.write(c);
}

char Arduino_getchar()
{
  char c;
  while (!Serial.available());
  return Serial.read();
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
  static uint8_t cnt;
  uint8_t ch;

  move (11, 10);
  addstr_P (PSTR("Timeout Counter: "));
  addstr (myitoa(cnt, buf));
  addstr_P (PSTR(" tenths of a sec"));
  clrtoeol ();

  move (10, 10);
  addstr_P (PSTR("Press a key (2x ESC or 5 seconds timeout exits): "));

  ch = Arduino_getchar();

  switch (ch)
  {
    case '\t':          addstr_P (PSTR("TAB"));         break;
    case '\r':          addstr_P (PSTR("CR"));          break;
    case KEY_ESCAPE:    addstr_P (PSTR("KEY_ESCAPE"));  break;
    case KEY_DOWN:      addstr_P (PSTR("KEY_DOWN"));    break;
    case KEY_UP:        addstr_P (PSTR("KEY_UP"));      break;
    case KEY_LEFT:      addstr_P (PSTR("KEY_LEFT"));    break;
    case KEY_RIGHT:     addstr_P (PSTR("KEY_RIGHT"));   break;
    case KEY_HOME:      addstr_P (PSTR("KEY_HOME"));    break;
    case KEY_DC:        addstr_P (PSTR("KEY_DC"));      break;
    case KEY_IC:        addstr_P (PSTR("KEY_IC"));      break;
    case KEY_NPAGE:     addstr_P (PSTR("KEY_NPAGE"));   break;
    case KEY_PPAGE:     addstr_P (PSTR("KEY_PPAGE"));   break;
    case KEY_END:       addstr_P (PSTR("KEY_END"));     break;
    case KEY_BTAB:      addstr_P (PSTR("KEY_BTAB"));    break;
    case KEY_F(1):      addstr_P (PSTR("KEY_F(1)"));    break;
    case KEY_F(2):      addstr_P (PSTR("KEY_F(2)"));    break;
    case KEY_F(3):      addstr_P (PSTR("KEY_F(3)"));    break;
    case KEY_F(4):      addstr_P (PSTR("KEY_F(4)"));    break;
    case KEY_F(5):      addstr_P (PSTR("KEY_F(5)"));    break;
    case KEY_F(6):      addstr_P (PSTR("KEY_F(6)"));    break;
    case KEY_F(7):      addstr_P (PSTR("KEY_F(7)"));    break;
    case KEY_F(8):      addstr_P (PSTR("KEY_F(8)"));    break;
    case KEY_F(9):      addstr_P (PSTR("KEY_F(9)"));    break;
    case KEY_F(10):     addstr_P (PSTR("KEY_F(10)"));   break;
    case KEY_F(11):     addstr_P (PSTR("KEY_F(11)"));   break;
    case KEY_F(12):     addstr_P (PSTR("KEY_F(12)"));   break;
    case ERR:           delay(100); cnt++;              break;
    default:            addch (ch);                     break;
  }

  if (ch != ERR)
  {
    cnt = 0;
    clrtoeol ();

    if (ch == KEY_ESCAPE)
    {
      delay(500);
      //break;
    }
  }
  else if (cnt >= 50 + 1)
  {
    //break;
  }

}
