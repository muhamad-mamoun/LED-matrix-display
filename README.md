# LED Matrix Display

This GitHub repository hosts the code and documentation for the LED matrix display project. The LED matrix display features an 8x32 configurable size and is capable of printing all 95 printable ASCII characters.



> [!IMPORTANT]
> This LED Matrix Display project is shared with the intention of fostering collaboration and learning within the open-source community. While you are welcome to use, modify, and distribute this code for personal and non-commercial purposes, we kindly request that you refrain from using it for commercial use without obtaining explicit permission from the project owner. Thank you for your understanding and cooperation. We appreciate your respect for the hard work put into its development.


# LED Matrix Display Project

## Overview

This GitHub repository hosts the code and documentation for a versatile LED matrix display project. The LED matrix display features an 8x32 configurable size and is capable of printing all 95 printable ASCII characters. Future improvements include support for Arabic and other language characters.

## Key Features

- Configurable size for the LED matrix display.
- Display speed and message size are adjustable.
- Uses the 74CH595 shift register for efficient control.
- Allows input of new strings via UART and USB connections.
- Supports mode switching through an external button using INT0 external interrupt.

## Software Architecture

The project follows a layered model architecture consisting of three layers:
- **MCAL (Microcontroller Abstraction Layer)**: Provides drivers for GPIO, UART, and External Interrupts.
- **HAL (Hardware Abstraction Layer)**: Includes the Shift Register and LED drivers.
- **APP (Application Layer)**: Contains the Display driver, enabling the display of English characters and strings using a character map, and the application files.

## Usage

This repository contains the code, documentation, and character map needed to implement and customize the LED matrix display project. The provided code is open-source and released under a specific license.

## Future Work

Future enhancements include storing character maps in External EEPROM and expanding character support to languages like Arabic. Contributions and collaborations are welcome!




## Contact

If you have any questions or need permission for commercial use, please contact the project owner:

###### muhamadmamoun@gmail.com