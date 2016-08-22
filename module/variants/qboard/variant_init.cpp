/*
  Copyright (c) 2016 Thibaut VIARD.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"
#include "core_private.h"

void initVariant( void )
{
  // Give PB4 to GPIO
  MATRIX->CCFG_SYSIO|=CCFG_SYSIO_SYSIO4;

  // Initialize Serial port Flexcom7 pins (EDBG)
//  pinPeripheral(PIN_SERIAL_RX, GPIO_PERIPH_B);
//  pinPeripheral(PIN_SERIAL_TX, GPIO_PERIPH_B);

#ifdef PIN_WINC3400_BASE
  // Initialize SPI port Flexcom5 pins (WINC3400 WiFi)
  pinPeripheral(PIN_WINC3400_MOSI, GPIO_PERIPH_A);
  pinPeripheral(PIN_WINC3400_MISO, GPIO_PERIPH_A);
  pinPeripheral(PIN_WINC3400_SCK, GPIO_PERIPH_A);
  pinPeripheral(PIN_WINC3400_SS, GPIO_PERIPH_A);

  pinMode(PIN_WINC3400_IRQN, INPUT);
  pinMode(PIN_WINC3400_WAKE, INPUT);
  pinMode(PIN_WINC3400_RESET, OUTPUT);
  digitalWrite(PIN_WINC3400_RESET, LOW);
  pinMode(PIN_WINC3400_CHIP_EN, OUTPUT);
  digitalWrite(PIN_WINC3400_CHIP_EN, LOW);
  pinMode(PIN_WINC3400_RTC_CLK, OUTPUT);
  digitalWrite(PIN_WINC3400_RTC_CLK, LOW);

  // Initialize Serial port Flexcom0 pins (WINC3400 BlueTooth)
//  pinPeripheral(PIN_WINC3400_BT_RX, GPIO_PERIPH_A);
//  pinPeripheral(PIN_WINC3400_BT_TX, GPIO_PERIPH_A);
//  pinPeripheral(PIN_WINC3400_BT_RTS, GPIO_PERIPH_A);
//  pinPeripheral(PIN_WINC3400_BT_CTS, GPIO_PERIPH_A);
#endif // PIN_WINC3400_BASE
}
