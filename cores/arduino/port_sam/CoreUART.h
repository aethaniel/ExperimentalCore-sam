/*
  Copyright (c) 2011 Arduino.  All right reserved.

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

#ifndef _UART_CLASS_
#define _UART_CLASS_

#include "CoreHardwareSerial.h"
#include "CoreRingBuffer.h"
#include "core_variant.h"

// Includes Atmel CMSIS
#include "sam.h"

class UARTClass : public HardwareSerial
{
  public:
    enum UARTModes {
      Mode_8N1 = US_MR_CHRL_8_BIT | US_MR_PAR_NO    | US_MR_NBSTOP_1_BIT,
      Mode_8E1 = US_MR_CHRL_8_BIT | US_MR_PAR_EVEN  | US_MR_NBSTOP_1_BIT,
      Mode_8O1 = US_MR_CHRL_8_BIT | US_MR_PAR_ODD   | US_MR_NBSTOP_1_BIT,
      Mode_8M1 = US_MR_CHRL_8_BIT | US_MR_PAR_MARK  | US_MR_NBSTOP_1_BIT,
      Mode_8S1 = US_MR_CHRL_8_BIT | US_MR_PAR_SPACE | US_MR_NBSTOP_1_BIT,

      Mode_5N1 = US_MR_CHRL_5_BIT | US_MR_PAR_NO    | US_MR_NBSTOP_1_BIT,
      Mode_6N1 = US_MR_CHRL_6_BIT | US_MR_PAR_NO    | US_MR_NBSTOP_1_BIT,
      Mode_7N1 = US_MR_CHRL_7_BIT | US_MR_PAR_NO    | US_MR_NBSTOP_1_BIT,
      Mode_5N2 = US_MR_CHRL_5_BIT | US_MR_PAR_NO    | US_MR_NBSTOP_2_BIT,
      Mode_6N2 = US_MR_CHRL_6_BIT | US_MR_PAR_NO    | US_MR_NBSTOP_2_BIT,
      Mode_7N2 = US_MR_CHRL_7_BIT | US_MR_PAR_NO    | US_MR_NBSTOP_2_BIT,
      Mode_8N2 = US_MR_CHRL_8_BIT | US_MR_PAR_NO    | US_MR_NBSTOP_2_BIT,

      Mode_5E1 = US_MR_CHRL_5_BIT | US_MR_PAR_EVEN  | US_MR_NBSTOP_1_BIT,
      Mode_6E1 = US_MR_CHRL_6_BIT | US_MR_PAR_EVEN  | US_MR_NBSTOP_1_BIT,
      Mode_7E1 = US_MR_CHRL_7_BIT | US_MR_PAR_EVEN  | US_MR_NBSTOP_1_BIT,
      Mode_5E2 = US_MR_CHRL_5_BIT | US_MR_PAR_EVEN  | US_MR_NBSTOP_2_BIT,
      Mode_6E2 = US_MR_CHRL_6_BIT | US_MR_PAR_EVEN  | US_MR_NBSTOP_2_BIT,
      Mode_7E2 = US_MR_CHRL_7_BIT | US_MR_PAR_EVEN  | US_MR_NBSTOP_2_BIT,
      Mode_8E2 = US_MR_CHRL_8_BIT | US_MR_PAR_EVEN  | US_MR_NBSTOP_2_BIT,

      Mode_5O1 = US_MR_CHRL_5_BIT | US_MR_PAR_ODD   | US_MR_NBSTOP_1_BIT,
      Mode_6O1 = US_MR_CHRL_6_BIT | US_MR_PAR_ODD   | US_MR_NBSTOP_1_BIT,
      Mode_7O1 = US_MR_CHRL_7_BIT | US_MR_PAR_ODD   | US_MR_NBSTOP_1_BIT,
      Mode_5O2 = US_MR_CHRL_5_BIT | US_MR_PAR_ODD   | US_MR_NBSTOP_2_BIT,
      Mode_6O2 = US_MR_CHRL_6_BIT | US_MR_PAR_ODD   | US_MR_NBSTOP_2_BIT,
      Mode_7O2 = US_MR_CHRL_7_BIT | US_MR_PAR_ODD   | US_MR_NBSTOP_2_BIT,
      Mode_8O2 = US_MR_CHRL_8_BIT | US_MR_PAR_ODD   | US_MR_NBSTOP_2_BIT,
      Mode_5M1 = US_MR_CHRL_5_BIT | US_MR_PAR_MARK  | US_MR_NBSTOP_1_BIT,
      Mode_6M1 = US_MR_CHRL_6_BIT | US_MR_PAR_MARK  | US_MR_NBSTOP_1_BIT,
      Mode_7M1 = US_MR_CHRL_7_BIT | US_MR_PAR_MARK  | US_MR_NBSTOP_1_BIT,
      Mode_5M2 = US_MR_CHRL_5_BIT | US_MR_PAR_MARK  | US_MR_NBSTOP_2_BIT,
      Mode_6M2 = US_MR_CHRL_6_BIT | US_MR_PAR_MARK  | US_MR_NBSTOP_2_BIT,
      Mode_7M2 = US_MR_CHRL_7_BIT | US_MR_PAR_MARK  | US_MR_NBSTOP_2_BIT,
      Mode_8M2 = US_MR_CHRL_8_BIT | US_MR_PAR_MARK  | US_MR_NBSTOP_2_BIT,

      Mode_5S1 = US_MR_CHRL_5_BIT | US_MR_PAR_SPACE | US_MR_NBSTOP_1_BIT,
      Mode_6S1 = US_MR_CHRL_6_BIT | US_MR_PAR_SPACE | US_MR_NBSTOP_1_BIT,
      Mode_7S1 = US_MR_CHRL_7_BIT | US_MR_PAR_SPACE | US_MR_NBSTOP_1_BIT,
      Mode_5S2 = US_MR_CHRL_5_BIT | US_MR_PAR_SPACE | US_MR_NBSTOP_2_BIT,
      Mode_6S2 = US_MR_CHRL_6_BIT | US_MR_PAR_SPACE | US_MR_NBSTOP_2_BIT,
      Mode_7S2 = US_MR_CHRL_7_BIT | US_MR_PAR_SPACE | US_MR_NBSTOP_2_BIT,
      Mode_8S2 = US_MR_CHRL_8_BIT | US_MR_PAR_SPACE | US_MR_NBSTOP_2_BIT,
    };
    UARTClass(Usart* pUsart, IRQn_Type irq, uint32_t id, uint32_t isUART);

    void begin(const uint32_t dwBaudRate);
    void begin(const uint32_t dwBaudRate, const UARTModes config);
    void end(void);
    int available(void);
    int availableForWrite(void);
    int peek(void);
    int read(void);
    void flush(void);
    size_t write(const uint8_t c);
    using Print::write; // pull in write(str) and write(buf, size) from Print

    void setInterruptPriority(uint32_t priority);
    uint32_t getInterruptPriority();

    void IrqHandler(void);

    operator bool() { return true; }; // UART always active

  protected:
    void init(const uint32_t dwBaudRate, const uint32_t config);

    RingBuffer _rx_buffer;
    RingBuffer _tx_buffer;

    Usart* _pUsart;
    IRQn_Type _dwIrq;
    uint32_t _dwId;
    boolean _isUART;
};

#endif // _UART_CLASS_
