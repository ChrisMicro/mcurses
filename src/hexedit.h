/*
   hexedit.h

   Created: 18.01.2017 08:24:04
    Author: ChrisMicro
*/

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef HEXEDIT_H_
#define HEXEDIT_H_

#include "mcurses.h"

void hexedit (uint16_t offset);
void setFunction_readMemory(uint8_t (*functionPointer)(uint16_t address));
void setFunction_writeMemory(void (*functionPointer)(uint16_t address, uint8_t value));

#endif /* HEXEDIT_H_ */

#ifdef __cplusplus
}
#endif
