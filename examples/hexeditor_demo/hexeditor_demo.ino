/*-----------------------------------------------------------------------------------------------------------------

   How to use the hexadecimal editor of MCURSES
   
   What:
    With this example you can edit the RAM-Memory contents of the ARDUINO.
   
   Why:
    This may be useful for debugging purposes

   Revision History:
   V1.0 2017 01 18 ChrisMicro, initial version

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

---------------------------------------------------------------------------------------------------------------*/

#include "hexedit.h"

void Arduino_putchar(uint8_t c)
{
  Serial.write(c);
}

char Arduino_getchar()
{
  // char c;
  while (!Serial.available());
  return Serial.read();
}

void setup()
{
  
  Serial.begin(115200);
  
  setFunction_putchar(Arduino_putchar); // tell the library which output channel shall be used
  setFunction_getchar(Arduino_getchar); // tell the library which input channel shall be used

  initscr();                            // initialize mcurses

}

void loop()
{
  static uint16_t    memmoryStartAddress = 0x100;    // ATMEGA RAM start

  hexedit (memmoryStartAddress);
  
  clear();
  char str[]="hexadecimal editor stopped";
  Serial.println(str);
  
  delay(3000);
}
