/*
 * TwoWire.h - TWI/I2C library for Arduino Due
 * Copyright (c) 2011 Cristian Maglie <c.maglie@arduino.cc>. All rights reserved.
 * Copyright (c) 2016 Thibaut VIARD.  All right reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

//extern "C"
//{
#include <string.h>
//}

#include "CoreWire.hpp"
#include "core_delay.h"
#include "core_private.h"

static inline bool TWI_FailedAcknowledge(Twi *_twi)
{
  return _twi->TWI_SR & TWI_SR_NACK;
}

static inline bool TWI_WaitTransferComplete(Twi *_twi, uint32_t _timeout)
{
  uint32_t _status_reg = 0;

  while ((_status_reg & TWI_SR_TXCOMP) != TWI_SR_TXCOMP)
  {
    _status_reg = _twi->TWI_SR;

    if (_status_reg & TWI_SR_NACK)
      return false;

    if (--_timeout == 0)
      return false;
  }
  return true;
}

static inline bool TWI_WaitByteSent(Twi *_twi, uint32_t _timeout)
{
  uint32_t _status_reg = 0;

  while ((_status_reg & TWI_SR_TXRDY) != TWI_SR_TXRDY)
  {
    _status_reg = _twi->TWI_SR;

    if (_status_reg & TWI_SR_NACK)
      return false;

    if (--_timeout == 0)
      return false;
  }

  return true;
}

static inline bool TWI_WaitByteReceived(Twi *_twi, uint32_t _timeout)
{
  uint32_t _status_reg = 0;

  while ((_status_reg & TWI_SR_RXRDY) != TWI_SR_RXRDY)
  {
    _status_reg = _twi->TWI_SR;

    if (_status_reg & TWI_SR_NACK)
      return false;

    if (--_timeout == 0)
      return false;
  }

  return true;
}

static inline bool TWI_STATUS_SVACC(uint32_t status)
{
  return (status & TWI_SR_SVACC) == TWI_SR_SVACC;
}

static inline bool TWI_STATUS_GACC(uint32_t status)
{
  return (status & TWI_SR_GACC) == TWI_SR_GACC;
}

static inline bool TWI_STATUS_EOSACC(uint32_t status)
{
  return (status & TWI_SR_EOSACC) == TWI_SR_EOSACC;
}

TwoWire::TwoWire(Twi *_twi, void(*_beginCb)(void)) :
  _pTwi(_twi), rxBufferIndex(0), rxBufferLength(0),
  txAddress(0), txBufferLength(0), srvBufferIndex(0), srvBufferLength(0),
  status( UNINITIALIZED), onBeginCallback(_beginCb), twiClock(TWI_CLOCK)
{
}

void TwoWire::begin(void)
{
  if (onBeginCallback)
  {
    onBeginCallback();
  }

  // Disable PDC channel
  _pTwi->TWI_PTCR = TWI_PTCR_RXTDIS | TWI_PTCR_TXTDIS;

  /* SVEN: TWI Slave Mode Enabled */
  _pTwi->TWI_CR = TWI_CR_SVEN ;
  /* Reset the TWI */
  _pTwi->TWI_CR = TWI_CR_SWRST ;
  _pTwi->TWI_RHR ;

  /* We disable first both Slave and Master */
  _pTwi->TWI_CR = TWI_CR_SVDIS ;
  _pTwi->TWI_CR = TWI_CR_MSDIS ;

  /* Then we set the Master mode */
  _pTwi->TWI_CR = TWI_CR_MSEN ;

  setClock( twiClock );

  status = MASTER_IDLE;
}

void TwoWire::begin(uint8_t address)
{
  if (onBeginCallback)
  {
    onBeginCallback();
  }

  // Disable PDC channel
  _pTwi->TWI_PTCR = TWI_PTCR_RXTDIS | TWI_PTCR_TXTDIS;

  /* TWI software reset */
  _pTwi->TWI_CR = TWI_CR_SWRST;
  _pTwi->TWI_RHR;

  /* Wait at least 10 ms */
  delay(10);

  /* TWI Slave Mode Disabled, TWI Master Mode Disabled*/
  _pTwi->TWI_CR = TWI_CR_SVDIS | TWI_CR_MSDIS;

  /* Configure slave address. */
  _pTwi->TWI_SMR = 0;
  _pTwi->TWI_SMR = TWI_SMR_SADR(address);

  /* SVEN: TWI Slave Mode Enabled */
  _pTwi->TWI_CR = TWI_CR_SVEN;

  /* Wait at least 10 ms */
  delay(10);

  status = SLAVE_IDLE;
  _pTwi->TWI_IER=TWI_IER_SVACC;
  //| TWI_IER_RXRDY | TWI_IER_TXRDY	| TWI_IER_TXCOMP);
}

void TwoWire::begin(int address)
{
  begin((uint8_t)address);
}

void TwoWire::setClock(uint32_t ulFrequency)
{
  uint32_t ulCkDiv = 0 ;
  uint32_t ulClDiv ;
  uint32_t ulResolved = 0 ;

  /* Configure clock */
  while ( !ulResolved )
  {
    ulClDiv = ((VARIANT_MCK / (2 * ulFrequency)) - 4) / (1<<ulCkDiv) ;

    if ( ulClDiv <= 255 )
    {
      ulResolved = 1 ;
    }
    else
    {
      ulCkDiv++ ;
    }
  }

//  assert( ulCkDiv < 8 ) ;

  _pTwi->TWI_CWGR = 0 ;
  _pTwi->TWI_CWGR = (ulCkDiv << 16) | (ulClDiv << 8) | ulClDiv ;

  twiClock = ulFrequency;
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop)
{
//  assert( (address & 0x80) == 0 ) ;

  if (quantity > BUFFER_LENGTH)
  {
    quantity = BUFFER_LENGTH;
  }

  // perform blocking read into buffer
  int bytes_read = 0;

  /* Set slave address and number of internal address bytes. */
  _pTwi->TWI_MMR = 0;
  _pTwi->TWI_MMR = (0 << 8) | TWI_MMR_MREAD | (address << 16);

  /* Set internal address bytes */
  _pTwi->TWI_IADR = 0;
  _pTwi->TWI_IADR = 0;

  /* Send START condition */
  _pTwi->TWI_CR = TWI_CR_START;

  do
  {
    // Stop condition must be set during the reception of last byte
    if (bytes_read + 1 == quantity)
    {
      _pTwi->TWI_CR |= TWI_CR_STOP;
    }

    TWI_WaitByteReceived(_pTwi, RECV_TIMEOUT);
    rxBuffer[bytes_read++] = _pTwi->TWI_RHR;
  } while (bytes_read < quantity);

  TWI_WaitTransferComplete(_pTwi, RECV_TIMEOUT);

  // set rx buffer iterator vars
  rxBufferIndex = 0;
  rxBufferLength = bytes_read;

  return bytes_read;
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity)
{
  return requestFrom((uint8_t) address, (uint8_t) quantity, (uint8_t) true);
}

uint8_t TwoWire::requestFrom(int address, int quantity)
{
  return requestFrom((uint8_t) address, (uint8_t) quantity, (uint8_t) true);
}

uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop)
{
  return requestFrom((uint8_t) address, (uint8_t) quantity, (uint8_t) sendStop);
}

void TwoWire::beginTransmission(uint8_t address)
{
  status = MASTER_SEND;

  // save address of target and empty buffer
  txAddress = address;
  txBufferLength = 0;
}

void TwoWire::beginTransmission(int address)
{
  beginTransmission((uint8_t) address);
}

//
//	Originally, 'endTransmission' was an f(void) function.
//	It has been modified to take one parameter indicating
//	whether or not a STOP should be performed on the bus.
//	Calling endTransmission(false) allows a sketch to
//	perform a repeated start.
//
//	WARNING: Nothing in the library keeps track of whether
//	the bus tenure has been properly ended with a STOP. It
//	is very possible to leave the bus in a hung state if
//	no call to endTransmission(true) is made. Some I2C
//	devices will behave oddly if they do not see a STOP.
//
uint8_t TwoWire::endTransmission(uint8_t sendStop)
{
  uint8_t error = 0;
  // transmit buffer (blocking)
  /* Set slave address and number of internal address bytes. */
  _pTwi->TWI_MMR = 0;
  _pTwi->TWI_MMR = (0 << 8) | (txAddress << 16);

  /* Set internal address bytes. */
  _pTwi->TWI_IADR = 0;
  _pTwi->TWI_IADR = 0;

  /* Write first byte to send.*/
  _pTwi->TWI_THR = txBuffer[0];

  if (!TWI_WaitByteSent(_pTwi, XMIT_TIMEOUT))
    error = 2;	// error, got NACK on address transmit

  if (error == 0)
  {
    uint16_t sent = 1;

    while (sent < txBufferLength)
    {
      _pTwi->TWI_THR=txBuffer[sent++];
      if (!TWI_WaitByteSent(_pTwi, XMIT_TIMEOUT))
        error = 3;	// error, got NACK during data transmmit
    }
  }

  if (error == 0)
  {
    _pTwi->TWI_CR = TWI_CR_STOP;

    if (!TWI_WaitTransferComplete(_pTwi, XMIT_TIMEOUT))
      error = 4;	// error, finishing up
  }

  txBufferLength = 0;		// empty buffer
  status = MASTER_IDLE;
  return error;
}

//	This provides backwards compatibility with the original
//	definition, and expected behaviour, of endTransmission
//
uint8_t TwoWire::endTransmission(void)
{
  return endTransmission(true);
}

size_t TwoWire::write(uint8_t data)
{
  if (status == MASTER_SEND)
  {
    if (txBufferLength >= BUFFER_LENGTH)
      return 0;
    txBuffer[txBufferLength++] = data;

    return 1;
  }
  else
  {
    if (srvBufferLength >= BUFFER_LENGTH)
      return 0;
    srvBuffer[srvBufferLength++] = data;

    return 1;
  }
}

size_t TwoWire::write(const uint8_t *data, size_t quantity)
{
  if (status == MASTER_SEND)
  {
    for (size_t i = 0; i < quantity; ++i)
    {
      if (txBufferLength >= BUFFER_LENGTH)
        return i;

      txBuffer[txBufferLength++] = data[i];
    }
  }
  else
  {
    for (size_t i = 0; i < quantity; ++i)
      {
      if (srvBufferLength >= BUFFER_LENGTH)
        return i;

      srvBuffer[srvBufferLength++] = data[i];
    }
  }
  return quantity;
}

int TwoWire::available(void)
{
  return rxBufferLength - rxBufferIndex;
}

int TwoWire::read(void)
{
  if (rxBufferIndex < rxBufferLength)
  {
    return rxBuffer[rxBufferIndex++];
  }

  return -1;
}

int TwoWire::peek(void)
{
  if (rxBufferIndex < rxBufferLength)
  {
    return rxBuffer[rxBufferIndex];
  }

  return -1;
}

void TwoWire::flush(void)
{
  // Do nothing, use endTransmission(..) to force
  // data transfer.
}

void TwoWire::onReceive(void(*function)(int))
{
  onReceiveCallback = function;
}

void TwoWire::onRequest(void(*function)(void))
{
  onRequestCallback = function;
}

void TwoWire::onService(void)
{
  // Retrieve interrupt status
  uint32_t sr = _pTwi->TWI_SR;

  if (status == SLAVE_IDLE && TWI_STATUS_SVACC(sr))
  {
    _pTwi->TWI_IDR=TWI_IDR_SVACC;
    _pTwi->TWI_IER=TWI_IER_RXRDY | TWI_IER_GACC | TWI_IER_NACK
                   | TWI_IER_EOSACC | TWI_IER_SCL_WS | TWI_IER_TXCOMP;

    srvBufferLength = 0;
    srvBufferIndex = 0;

    // Detect if we should go into RECV or SEND status
    // SVREAD==1 means *master* reading -> SLAVE_SEND
    if ((sr & TWI_SR_SVREAD) != TWI_SR_SVREAD)
    {
      status = SLAVE_RECV;
    }
    else
    {
      status = SLAVE_SEND;

      // Alert calling program to generate a response ASAP
      if (onRequestCallback)
      {
        onRequestCallback();
      }
      else
      {
        // create a default 1-byte response
        write((uint8_t) 0);
      }
    }
  }

  if (status != SLAVE_IDLE)
  {
    if (((sr & TWI_SR_TXCOMP) == TWI_SR_TXCOMP) && TWI_STATUS_EOSACC(sr))
    {
      if (status == SLAVE_RECV && onReceiveCallback)
      {
        // Copy data into rxBuffer
        // (allows to receive another packet while the
        // user program reads actual data)
        for (uint8_t i = 0; i < srvBufferLength; ++i)
        {
          rxBuffer[i] = srvBuffer[i];
        }
        rxBufferIndex = 0;
        rxBufferLength = srvBufferLength;

        // Alert calling program
        onReceiveCallback( rxBufferLength);
      }

      // Transfer completed
      _pTwi->TWI_IER=TWI_SR_SVACC;
      _pTwi->TWI_IDR=TWI_IDR_RXRDY | TWI_IDR_GACC | TWI_IDR_NACK
                     | TWI_IDR_EOSACC | TWI_IDR_SCL_WS | TWI_IER_TXCOMP;
      status = SLAVE_IDLE;
    }
  }

  if (status == SLAVE_RECV)
  {
    if ((sr & TWI_SR_RXRDY) == TWI_SR_RXRDY)
    {
      if (srvBufferLength < BUFFER_LENGTH)
        srvBuffer[srvBufferLength++] = _pTwi->TWI_RHR;
    }
  }

  if (status == SLAVE_SEND)
  {
    if (((sr & TWI_SR_TXRDY) == TWI_SR_TXRDY) && ((status & TWI_SR_NACK) != TWI_SR_NACK))
    {
      uint8_t c = 'x';
      if (srvBufferIndex < srvBufferLength)
      {
        c = srvBuffer[srvBufferIndex++];
      }
      _pTwi->TWI_THR = c;
    }
  }
}
