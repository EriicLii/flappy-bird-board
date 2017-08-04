# flappy-bird-board
A circuit board built to play a flappy bird clone, run by an ATMega328P and displayed on a Nokia 5110.

The perf-board design is meant to be used on a 5 x 7cm - 18 x 24 pad single-sided perforated prototyping board.
The triple pad design of switches S1 and S3 is done intentionally to be compatible with the following:
  - Small SPDT switches
  - Header with a shunt jumper
  - Wires leading directly to a SPST switch

S2 is the button used primarily for jumping in the game, which a default-off momentary push button would be ideal for.

U3 is a boost converter module that provides 5v to power the circuit. It is meant to be separate from the perfboard, and take the input from two AAA batteries to allow the board to be portable. The boost converter is optional and can be swapped out with any stable 5v input such as USB. 

The Nokia 5110 LCD board used is one similar to this one: https://www.sparkfun.com/products/10168 (However with different pin positions)

Two sets of 1x8 female headers are to be soldered to the perfboard onto which the LCD will be set. The LCD is orientated from pin 8 to pin 1 left to right on the board. If standard female headers with a receptacle depth of 6mm are used, there will be enough clearance for the components in between the perforated board and the LCD board. A 28-pin IC socket is to be soldered onto the board and used with the ATMega328-P chip. The speaker used on the board is a small buzzer, however it can be substituted with two wires soldered onto a speaker.
