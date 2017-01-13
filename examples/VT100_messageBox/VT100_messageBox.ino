#include "mcurses.h"

void Arduino_putchar(uint8_t c)
{
  Serial.write(c);
}

void setup()
{
  Serial.begin(115200);

  setFunction_putchar(Arduino_putchar); // tell the library which output channel shall be used

  initscr();                  // initialize mcurses
  move (11, 15);              // set cursor position
  addstr ("Hello, World");    // show text
  delay(5000);
  endwin ();                  // end mcurses
}

void loop()
{

}
