/*-----------------------------------------------------------------------------------------------------------------

   How to use the hexadecimal editor of MCURSES
   to edit the EEPROM values of an ARDUINO

   What:
    With this example you can edit the EEPROM-Memory contents of the ARDUINO.

   Why:
    This may be useful to change the EEPROM contents directly in the microcontroller

   Hint:
    to exit the editor, press two times ESC

   Revision History:
   V1.0 2019 01 22 ChrisMicro, initial version

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

  ---------------------------------------------------------------------------------------------------------------*/

#include <EEPROM.h>
#include "hexedit.h"


void Arduino_putchar(uint8_t c)
{
  Serial.write(c);
}

char Arduino_getchar()
{
  while (!Serial.available());
  return Serial.read();
}

void Arduino_writeEEPROM(uint16_t address, uint8_t value)
{
  if(address<EEPROM.length()) EEPROM.write(address, value);
}

uint8_t Arduino_readEEPROM(uint16_t address)
{
  if(address<EEPROM.length()) return (uint8_t) EEPROM.read(address);
  else return 0;
}

void setup()
{

  Serial.begin(115200);

  setFunction_putchar(Arduino_putchar); // tell the library which output channel shall be used
  setFunction_getchar(Arduino_getchar); // tell the library which input channel shall be used
  setFunction_readMemory(Arduino_readEEPROM);
  setFunction_writeMemory(Arduino_writeEEPROM);

  initscr();                            // initialize mcurses

}

void loop()
{
  static uint16_t    memmoryStartAddress = 0;   

  hexedit (memmoryStartAddress);

  clear();
  char str[] = "hexadecimal editor stopped";
  Serial.println(str);

  delay(3000);
}
