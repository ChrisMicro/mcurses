/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * @file hexedit.c - full screen hex editor
 *
 * Copyright (c) 2014 Frank Meyer - frank(at)fli4l.de
 *
 * Revision History:
 * V1.0 2015 xx xx Frank Meyer, original version
 * V1.1 2017 01 14 ChrisMicro, converted to Arduino example
 * V1.2 2019 01 22 ChrisMicro, memory access functions can now be set
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Possible keys:
 *  LEFT                back one byte
 *  RIGHT               forward one byte
 *  DOWN                one line down
 *  UP                  one line up
 *  TAB                 toggle between hex and ascii columns
 *  any other           input as hex or ascii value
 *  2 x ESCAPE          exit
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */

#include "mcurses.h"
//Beginning of Auto generated function prototypes by Atmel Studio
void itox(uint8_t val);
void itoxx(unsigned char i);
uint8_t xtoi(uint8_t ch);
void print_hex_line(uint8_t line, uint16_t off);
void hexedit(uint16_t offset);

//End of Auto generated function prototypes by Atmel Studio

#define FIRST_LINE      1
#define LAST_LINE       (LINES - 1)

#define BYTES_PER_ROW   16
#define FIRST_HEX_COL   7
#define FIRST_ASCII_COL 57
#define LAST_BYTE_COL   (FIRST_HEX_COL + 3 * BYTES_PER_ROW)
#define IS_PRINT(ch)    (((ch) >= 32 && (ch) < 0x7F) || ((ch) >= 0xA0))

#define MODE_HEX        0
#define MODE_ASCII      1

#define IS_HEX(ch)      (((ch) >= 'A' && (ch) <= 'F') || ((ch) >= 'a' && (ch) <= 'f') || ((ch) >= '0' && (ch) <= '9'))

/*
#ifdef unix
#define PEEK(x)         memory[x]
#define POKE(x,v)       memory[x] = (v)
unsigned char           memory[65536];
#else // SDCC
#define PEEK(x)         *((unsigned char *) (x))
#define POKE(x,v)       *((unsigned char *) (x)) = (v)
#endif
*/
// default functions are RAM access functons by pointers
uint8_t peekMemory(uint16_t address)
{
  uint8_t *p;
  return p[address];
}
void    pokeMemory(uint16_t address, uint8_t value)
{
  uint8_t *p;
  p[address]=value;
}

uint8_t (*FunctionPointer_readMemory)(uint16_t address)=peekMemory; // set default function
void  (*FunctionPointer_writeMemory)(uint16_t address, uint8_t value)=pokeMemory; // set default function

#define PEEK(x) FunctionPointer_readMemory(x)
#define POKE(x,v) FunctionPointer_writeMemory(x,v)

void setFunction_readMemory(uint8_t (*functionPointer)(uint16_t address))
{
  FunctionPointer_readMemory = functionPointer;
}

void setFunction_writeMemory(void (*functionPointer)(uint16_t address, uint8_t value))
{
  FunctionPointer_writeMemory = functionPointer;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * itox: convert a decimal value 0-15 into hexadecimal digit
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void itox (uint8_t val)
{
    uint8_t ch;

    val &= 0x0F;

    if (val <= 9)
    {
        ch = val + '0';
    }
    else
    {
        ch = val - 10 + 'A';
    }
    addch (ch);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * itoxx: convert a decimal value 0-255 into 2 hexadecimal digits
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void itoxx (unsigned char i)
{
    itox (i >> 4);
    itox (i & 0x0F);
}

uint8_t xtoi (uint8_t ch)
{
    uint8_t val;

    if (ch >= 'A' && ch <= 'F')
    {
        val = (ch - 'A') + 10;
    }
    else if (ch >= 'a' && ch <= 'f')
    {
        val = (ch - 'a') + 10;
    }
    else
    {
        val = (ch - '0');
    }
    itox (val);     // print value in hex
    return val;
}

void print_hex_line (uint8_t line, uint16_t off)
{
    uint8_t         col;
    uint8_t         ch;

    move (line, 0);
    itoxx (off >> 8);
    itoxx (off & 0xFF);

    move (line, FIRST_HEX_COL);
    for (col = 0; col < BYTES_PER_ROW; col++)
    {
        itoxx (PEEK(off));
        addch (' ');
        off++;
    }

    off -= BYTES_PER_ROW;

    move (line, FIRST_ASCII_COL);

    for (col = 0; col < BYTES_PER_ROW; col++)
    {
        ch = PEEK(off);

        if (IS_PRINT(ch))
        {
            addch (ch);
        }
        else
        {
            addch ('.');
        }
        off++;
    }
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * hexdit: hex editor
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void hexedit (uint16_t offset)
{
    uint8_t         ch;
    uint8_t         line;
    uint8_t         col;
    uint16_t        off;
    uint8_t         byte;
    uint8_t         mode = MODE_HEX;

    clear ();
    setscrreg (FIRST_LINE, LAST_LINE);

    off = offset;

    move (0, 0);
    attrset (A_REVERSE);

    for (col = 0; col < FIRST_HEX_COL; col++)
    {
        addch (' ');
    }

    for (byte = 0; byte < BYTES_PER_ROW; byte++)
    {
        itoxx (byte);
        addch (' ');
        col += 3;
    }

    for ( ; col < FIRST_ASCII_COL; col++)
    {
        addch (' ');
    }

    for (byte = 0; byte < BYTES_PER_ROW; byte++)
    {
        itox (byte);
    }

    attrset (A_NORMAL);

    for (line = FIRST_LINE; line < LAST_LINE; line++)
    {
        print_hex_line (line, off);
        off += BYTES_PER_ROW;
    }

    off = offset;
    line = FIRST_LINE;
    col = FIRST_HEX_COL;
    byte = 0;

    do
    {
        move (line, col);
        ch = getch ();

        switch (ch)
        {
            case KEY_RIGHT:
            {
                if (byte < BYTES_PER_ROW - 1)
                {
                    byte++;
                    col += (mode == MODE_HEX) ? 3 : 1;
                }
                break;
            }
            case KEY_LEFT:
            {
                if (byte > 0)
                {
                    byte--;
                    col -= (mode == MODE_HEX) ? 3 : 1;
                }
                break;
            }
            case KEY_DOWN:
            {
                if (off < 65520)
                {
                    off += BYTES_PER_ROW;

                    if (line == LAST_LINE - 1)
                    {
                        scroll ();
                        print_hex_line (line, off);
                    }
                    else
                    {
                        line++;
                    }
                }
                break;
            }
            case KEY_UP:
            {
                if (off >= BYTES_PER_ROW)
                {
                    off -= BYTES_PER_ROW;

                    if (line == FIRST_LINE)
                    {
                        insertln ();
                        print_hex_line (line, off);
                    }
                    else
                    {
                        line--;
                    }
                }
                break;
            }
            case KEY_TAB:
            {
                if (mode == MODE_HEX)
                {
                    mode = MODE_ASCII;
                    col = FIRST_ASCII_COL + byte;
                }
                else
                {
                    mode = MODE_HEX;
                    col = FIRST_HEX_COL + 3 * byte;
                }
            }    /* fall through */
            default:
            {
                if (mode == MODE_HEX)
                {
                    if (IS_HEX(ch))
                    {
                        uint16_t    addr  = off + byte;
                        uint8_t     value = xtoi (ch) << 4;

                        ch = getch ();

                        if (IS_HEX(ch))
                        {
                            value |= xtoi (ch);
                            POKE(addr, value);
                            move (line, FIRST_ASCII_COL + byte);

                            if (IS_PRINT(value))
                            {
                                addch (value);
                            }
                            else
                            {
                                addch ('.');
                            }
                        }
                    }
                }
                else // MODE_ASCII
                {
                    if (IS_PRINT(ch))
                    {
                        uint16_t addr = off + byte;
                        POKE(addr, ch);
                        addch (ch);
                        move (line, FIRST_HEX_COL + 3 * byte);
                        itoxx (ch);
                    }
                }
            }
        }
    } while (ch != KEY_ESCAPE);
}

