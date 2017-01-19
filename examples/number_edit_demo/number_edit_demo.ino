/*-----------------------------------------------------------------------------------------------------------------

   Edit an integer number with the line editor 

   Revision History:
   V1.0 2017 01 18 ChrisMicro, initial version

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

  ---------------------------------------------------------------------------------------------------------------*/

#include "editor.h"

void Arduino_putchar(uint8_t c)
{
  Serial.write(c);
}

char Arduino_getchar()
{
  while (!Serial.available());
  return Serial.read();
}

void setup()
{
  Serial.begin(115200);

  setFunction_putchar(Arduino_putchar); // tell the library which output channel shall be used
  setFunction_getchar(Arduino_getchar); // tell the library which input channel shall be used

  initscr();                            // initialize MCURSES

  clear();
  Serial.println("Line Editor Demo");
  delay(3000);
  clear();

  move(5,15);
  Serial.println("edit number");
}

void loop()
{
  static int32_t number=1234;
  
  move (6, 15);              // set cursor position
  
  number = editInt16(number);

  move (10, 15);              // set cursor position    
  
  Serial.println("");
  Serial.print("the number is: ");
  Serial.print(number);Serial.println("        ");
  
  delay(1000);
}

