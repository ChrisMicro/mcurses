/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * mcurses towers of hanoi
 *
 * Copyright (c) 2011-2015 Frank Meyer - frank(at)fli4l.de
 *
 * Revision History:
 * V1.0 2015 xx xx Frank Meyer, original version
 * V1.1 2017 01 14 ChrisMicro, converted to Arduino example
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
#include "mcurses.h"

static uint8_t  hanoi_pole_height[3];
static uint8_t  hanoi_number_of_rings;

// set_position: set position on pole
void hanoi_set_position (uint8_t pole, uint8_t ring)
{
  uint8_t column;
  uint8_t line;

  column = pole * 20 - ring - 3;
  line = hanoi_number_of_rings + 5 - hanoi_pole_height[pole - 1];
  move (line, column);
}

// erase ring on pole
void hanoi_erase_ring (uint8_t ring, uint8_t pole)
{
  uint8_t i;
  hanoi_set_position (pole, ring + 1);
  hanoi_pole_height[pole - 1]--;

  i = ring + 3;

  while (i--)
  {
    addch (' ');
  }

  if (hanoi_pole_height[pole - 1] - 1 == hanoi_number_of_rings)
  {
    addch (' ');
  }
  else
  {
    addch ('|');
  }

  i = ring + 3;

  while (i--)
  {
    addch (' ');
  }

}

// draw ring on pole
void hanoi_draw_ring (uint8_t ring, uint8_t pole)
{
  uint8_t i;

  hanoi_pole_height[pole - 1]++;
  hanoi_set_position (pole, ring);

  i = 2 * ring + 5;

  while (i--)
  {
    addch ('-');
  }
}


// move ring from pole to pole
void hanoi_move_ring (uint8_t ring, uint8_t from_pole, uint8_t to_pole)
{
  uint8_t height[3];
  uint8_t h;
  uint8_t i;

  height[0] = hanoi_pole_height[0];
  height[1] = hanoi_pole_height[1];
  height[2] = hanoi_pole_height[2];

  h = hanoi_number_of_rings - height[from_pole - 1] + 2;

  while (h)
  {
    hanoi_erase_ring (ring, from_pole);
    move (3, 0);
    delay (100);
    hanoi_pole_height[from_pole - 1]++;
    hanoi_draw_ring (ring, from_pole);
    move (3, 0);
    delay (100);
    h--;
  }

  if (from_pole > to_pole)
  {
    for (i = 0; i < 20 * (from_pole - to_pole); i++)
    {
      mvdelch (3, 0);
      delay (25);
    }
  }
  else
  {
    for (i = 0; i < 20 * (to_pole - from_pole); i++)
    {
      mvinsch (3, 0, ' ');
      delay (25);
    }
  }

  i = hanoi_number_of_rings - height[to_pole - 1] + 1;
  hanoi_pole_height[to_pole - 1] = hanoi_number_of_rings + 1;

  while (i)
  {
    hanoi_draw_ring (ring, to_pole);
    move (3, 0);
    delay (100);
    hanoi_erase_ring (ring, to_pole);
    move (3, 0);
    delay (100);
    hanoi_pole_height[to_pole - 1]--;
    i--;
  }

  hanoi_draw_ring (ring, to_pole);
  move (3, 0);
  delay (100);

  hanoi_pole_height[from_pole - 1] = height[from_pole - 1] - 1;
  hanoi_pole_height[to_pole   - 1] = height[to_pole   - 1] + 1;
}

void hanoi (uint8_t nrings, uint8_t n1, uint8_t n2, uint8_t n3)
{
  uint8_t n;

  if (nrings == 0)
  {
    return;
  }

  n = nrings - 1;
  hanoi (n, n1, n3, n2);
  hanoi_move_ring (n, n1, n2);
  hanoi (n, n3, n2, n1);
}

void hanoi_draw_poles (void)
{
  uint8_t ring;
  uint8_t height_poles;
  uint8_t h;
  uint8_t i;
  uint8_t j;

  ring = hanoi_number_of_rings;
  height_poles = 1 + hanoi_number_of_rings;
  h = height_poles;

  while (h--)
  {
    for (i = 0; i < 3; i++)
    {
      mvaddch (h + 4, i * 20 + 19, '|');
    }
  }

  move (height_poles + 4, 0);

  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 19; j++)
    {
      addch ('-');
    }

    if (i != 3)
    {
      addch ('^');
    }
  }

  while (ring)
  {
    hanoi_draw_ring (ring, 1);
    ring--;
  }
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
  clear ();
  hanoi_number_of_rings = 4;
  hanoi_pole_height[0] = 0;
  hanoi_pole_height[1] = 0;
  hanoi_pole_height[2] = 0;

  hanoi_draw_poles ();
  hanoi (hanoi_number_of_rings, 1, 2, 3);
  delay (1000);
}
