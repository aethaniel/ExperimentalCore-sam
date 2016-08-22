/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@arduino.cc>
 * Copyright (c) 2014 by Paul Stoffregen <paul@pjrc.com> (Transaction API)
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#ifndef _ARDUINO_CORE_SPI_HPP_
#define _ARDUINO_CORE_SPI_HPP_

#include "variant.h"
#include "core_constants.h"
//#include <stdio.h>

/*
#ifndef SPI_INTERFACES_COUNT
#  define SPI_INTERFACES_COUNT 0
#endif

#if SPI_INTERFACES_COUNT == 0
#  define SPI_INTERFACES_COUNT 0
#  define SPI_CHANNELS_NUM     0
#endif
*/

/*
 * We won't compile SPI class if there isn't any SPI object definitions
 */
#if SPI_INTERFACES_COUNT > 0

// For compatibility with sketches designed for AVR @ 16 MHz
// New programs should use SPI.beginTransaction to set the SPI clock
#define SPI_CLOCK_DIV2	 11
#define SPI_CLOCK_DIV4	 21
#define SPI_CLOCK_DIV8	 42
#define SPI_CLOCK_DIV16	 84
#define SPI_CLOCK_DIV32	 168
#define SPI_CLOCK_DIV64	 255
#define SPI_CLOCK_DIV128 255

// SPI_HAS_TRANSACTION means SPIClass has
//   - beginTransaction()
//   - endTransaction()
//   - usingInterrupt()
//   - SPISetting(clock, bitOrder, dataMode)
#define SPI_HAS_TRANSACTION 1

// SPI_HAS_EXTENDED_CS_PIN_HANDLING means SPI has automatic
// CS pin handling and provides the following methods:
//   - begin(pin)
//   - end(pin)
//   - setBitOrder(pin, bitorder)
//   - setDataMode(pin, datamode)
//   - setClockDivider(pin, clockdiv)
//   - transfer(pin, data, SPI_LAST/SPI_CONTINUE)
//   - beginTransaction(pin, SPISettings settings) (if transactions are available)
#define SPI_HAS_EXTENDED_CS_PIN_HANDLING 1

#define SPI_MODE0 0x02
#define SPI_MODE1 0x00
#define SPI_MODE2 0x03
#define SPI_MODE3 0x01

enum SPITransferMode
{
  SPI_CONTINUE,
  SPI_LAST
};

class SPISettings
{
public:
  SPISettings(uint32_t clock, BitOrder bitOrder, uint8_t dataMode)
  {
    if (__builtin_constant_p(clock))
    {
      init_AlwaysInline(clock, bitOrder, dataMode);
    }
    else
    {
      init_MightInline(clock, bitOrder, dataMode);
    }
  }

  SPISettings(void)
  {
    init_AlwaysInline(4000000, MSBFIRST, SPI_MODE0);
  }

private:
  void init_MightInline(uint32_t clock, BitOrder bitOrder, uint8_t dataMode)
  {
    init_AlwaysInline(clock, bitOrder, dataMode);
  }

  void init_AlwaysInline(uint32_t clock, BitOrder bitOrder, uint8_t dataMode) __attribute__((__always_inline__))
  {
#if 0
    border = bitOrder;
    uint8_t div;

    if (clock < (F_CPU / 255))
    {
      div = 255;
    }
    else
    {
      if (clock >= (F_CPU / 2))
      {
        div = 2;
      }
      else
      {
        div = (F_CPU / (clock + 1)) + 1;
      }
    }
    config = (dataMode & 3) | SPI_CSR_CSAAT | SPI_CSR_SCBR(div) | SPI_CSR_DLYBCT(1);
#endif // 0
  }

  uint32_t config;
  BitOrder border;
  friend class SPIClass;
};

class SPIClass
{
  public:
  SPIClass(Spi *_spi, uint32_t _id, uint32_t _defaultSS, void(*_initCb)(void));

  // Transfer functions
  byte transfer(byte _pin, uint8_t _data, SPITransferMode _mode = SPI_LAST);
  void transfer(byte _pin, void *_buf, size_t _count, SPITransferMode _mode = SPI_LAST);
  // Transfer functions on default pin defaultSS
  byte transfer(uint8_t _data, SPITransferMode _mode = SPI_LAST) { return transfer(defaultSS, _data, _mode); }
  void transfer(void *_buf, size_t _count, SPITransferMode _mode = SPI_LAST) { transfer(defaultSS, _buf, _count, _mode); }

  // Transaction Functions
  void usingInterrupt(uint8_t interruptNumber);
  void beginTransaction(SPISettings settings) { beginTransaction(defaultSS, settings); }
  void beginTransaction(uint8_t pin, SPISettings settings);
  void endTransaction(void);

  // SPI Configuration methods
  void attachInterrupt(void);
  void detachInterrupt(void);

  void begin(void);
  void end(void);

  // Attach/Detach pin to/from SPI controller
  void begin(uint8_t _pin);
  void end(uint8_t _pin);

  // These methods sets a parameter on a single pin
  void setBitOrder(uint8_t _pin, BitOrder);
  void setDataMode(uint8_t _pin, uint8_t);
  void setClockDivider(uint8_t _pin, uint8_t);

  // These methods sets the same parameters but on default pin defaultSS
  void setBitOrder(BitOrder _order) { setBitOrder(defaultSS, _order); }
  void setDataMode(uint8_t _mode) { setDataMode(defaultSS, _mode); }
  void setClockDivider(uint8_t _div) { setClockDivider(defaultSS, _div); }

  private:
    void init();

    Spi *spi;
    uint32_t id;
    uint32_t defaultSS;
    BitOrder bitOrder[SPI_CHANNELS_NUM];
    uint32_t divider[SPI_CHANNELS_NUM];
    uint32_t mode[SPI_CHANNELS_NUM];
    void (*initCb)(void);
    bool initialized;
    uint8_t interruptMode;    // 0=none, 1-15=mask, 16=global
    uint8_t interruptSave;    // temp storage, to restore state
    uint32_t interruptMask[4];
};

#endif // SPI_INTERFACES_COUNT > 0

#endif // _ARDUINO_CORE_SPI_HPP_
