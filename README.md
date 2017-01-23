# mcurses

"mcurses" is a minimized version of programming library [ncurses](https://en.wikipedia.org/wiki/Ncurses) which gives GUI like interfaces on text terminal.

The library [mcurses](http://www.mikrocontroller.net/articles/MCURSES) was originally written by Frank M. for a set of microcontrollers.

This version runs directly on Arduinos.
In fact you could use this software on any microcontroller.
The serial driver interfaces are replace by call-back-function so you can hook any In-Output to the library.
This looks as follows:

```
setFunction_putchar(Arduino_putchar); // tell the library which output channel shall be used
setFunction_getchar(Arduino_getchar); // tell the library which input channel shall be used  
```
Please take a look into the examples to see how it is to be done exactly.
  
## What do you need to use this Library?

You need to install a **terminal programm** on your computer to interace to the serial line of the microcontroller.
The Arduino IDE has a build in serial terminal but for this libray the terminal has to emulate the VT220 standard.
The Arduino termianl does not to this and therfore you need a separate termainl program.

On Windows you can uses for example

- PuTTY
- teraterm

There may be several others but his two I have tested.

## Examples

### Temperature Demo
The "temperature_demo" displayes bar graphs of a simulated disk storage.

<p align="center">
  <img src="screenshot.png" width="640"/>
</p>

### Hex Editor Demo 
Here is the "hexeditor_demo". In this picture it is running on an ARDUINO UNO but you can easily include it on any microcontroller.

<p align="center">
  <img src="/doc/hexedit.png" width="640"/>
</p>



