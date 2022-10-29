# CATCH - A - BOO :ghost:

A simple ghosty point-catcher game using LCD-display I spent way too much time on. (Arduino Project)

## Playing the game

**Catch points with the ghost!** It is *that* simple.

There is an endless and a timer mode. It can be choosen at the beginning by pressing or toggling the joystick. 
If the joystick is pressed during game it will terminate immediately. 
The score and time will be displayed at the end.

Playing again requires pressing the restart button on the Arduino board, or switching the power on and off.

## Required tools

- Arduino Uno *(should work with other boards too)*
- LCD display *(20\*4 is preferable)*
- Joystick
- Resistors and jumper cables

## Library dependencies

This project uses the [LiquidCrystal](https://github.com/arduino-libraries/LiquidCrystal) library. 
It can be installed using the Arduino IDE Library Manager.

## Setup

**The column and row variables have to be adjusted according to the used display!**

`const int column = <LCD_width>, row = <LCD_heigth>`

Below is my wiring, but that can be easily overwritten at the beginning of the code. 
I used the LCD display in 4 bit mode.

### LCD display:

| VSS | VDD | VO | RS | RW | E | D0 - D3 | D4 - D7 | A | K |
| :-: | :-: | -- | -- | -- | - | :-----: | :-----: | - | - |
| GND | 5V | 3-4K resistor -> GND | 12 | GND | 11 | not connected | 5 - 2 |  220 resistor -> 5V  | GND |

### Joystick:

| GND | +5V | VRx | VRy | SW |
| :-: | :-: | :-: | :-: | -- |
| GND | 5V | A0 | A1 | A2 |
