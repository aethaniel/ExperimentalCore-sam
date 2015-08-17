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

#ifndef _USART_CLASS_
#define _USART_CLASS_

#include "CoreUART.h"
#include "CoreRingBuffer.h"

// Includes Atmel CMSIS
#include "sam.h"

class USARTClass : public UARTClass
{
  public:
    USARTClass(Usart* pUsart, IRQn_Type dwIrq, uint32_t dwId);

    void begin(const uint32_t dwBaudRate);
    void begin(const uint32_t dwBaudRate, const uint32_t config);

  protected:
    Usart* _pUsart;
};

#endif // _USART_CLASS_
