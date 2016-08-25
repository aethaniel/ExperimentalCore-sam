# Atmel SAM G55 MTP Bootloader

## 1- Prerequisites

The project build is based on Makefile system.
Makefile is present at project root and try to handle multi-platform cases.

Multi-plaform GCC is provided by ARM here: https://launchpad.net/gcc-arm-embedded/+download

Atmel Studio contains both make and ARM GCC toolchain. You don't need to install them in this specific use case.

For all builds and platforms you will need to have the Arduino IDE installed and the board support
package for "Arduino SAM Boards (32-bits ARM Cortex-M3)". You can install the latter
from the former's "Boards Manager" UI.

### Windows

* Native command line
Make binary can be obtained here: http://gnuwin32.sourceforge.net/packages/make.htm

* Cygwin/MSys/MSys2/Babun/etc...
It is available natively in all distributions.

* Atmel Studio
An Atmel Studio **7** Makefile-based project is present at project root, just open bossa_samg55.atsln file in AS7.

### Linux

Make is usually available by default.

### OS X

Make is available through XCode package.


## 2- Behaviour

This bootloader implements the wait for User Button.
By pressing this button at reset, the board will stay in bootloader, waiting for communication on USB Media Transfer Protocol.

## 3- Description

**Pinmap**

The following pins are used by the program :
PA22 : input/output (USB DP)
PA21 : input/output (USB DM)

**Clock system**

CPU runs at 8MHz from Internal Fast RC.

USB is driven by PLLB with source from internal/external 32kHz.

**Memory Mapping**

Bootloader code will be located at 0x0 and executed before any applicative code.

Applications compiled to be executed along with the bootloader will start at 0x2000 (see linker script bootloader_samg55j19.ld).

Before jumping to the application, the bootloader changes the VTOR register to use the interrupt vectors of the application @0x2000.<- not required as application code is taking care of this.
