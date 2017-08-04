# flappy-bird-board
A circuit board built to play a flappy bird clone, run by an ATMega328P and displayed on a Nokia 5110.

The perf-board design is meant to be used on a 5 x 7cm - 18 x 24 pad single-sided perforated prototyping board.
The triple pad design of switches S1 and S3 is done intentionally to be compatible with the following:
  - Small SPDT switches
  - Header with a shunt jumper
  - Wires leading directly to a SPST switch

S2 is the button used primarily for jumping in the game, which a default-off momentary push button would be ideal for.

U3 is a boost converter module that provides 5v to power the circuit. It is meant to be separate from the perfboard, and take the input from two AAA batteries to allow the board to be portable. The boost converter is optional aand can be swapped out with any stable 5v input such as USB. 
