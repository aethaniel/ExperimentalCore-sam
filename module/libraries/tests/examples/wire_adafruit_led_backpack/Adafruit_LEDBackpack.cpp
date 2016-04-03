/***************************************************
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED Matrix backpacks
  ----> http://www.adafruit.com/products/
  ----> http://www.adafruit.com/products/

  These displays use I2C to communicate, 2 pins are required to
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_LEDBackpack.h"

#ifndef _BV
  #define _BV(bit) (1<<(bit))
#endif

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif

void Adafruit_LEDBackpack::setBrightness(uint8_t b)
{
  if (b > 15)
  {
    b = 15;
  }

  Wire.beginTransmission(i2c_addr);
  Wire.write(HT16K33_CMD_BRIGHTNESS | b);
  Wire.endTransmission();
}

void Adafruit_LEDBackpack::blinkRate(uint8_t b)
{
  Wire.beginTransmission(i2c_addr);

  if (b > 3)
  {
    b = 0; // turn off if not sure
  }

  Wire.write(HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (b << 1));
  Wire.endTransmission();
}

Adafruit_LEDBackpack::Adafruit_LEDBackpack(void)
{
}

void Adafruit_LEDBackpack::begin(uint8_t _addr = 0x70)
{
  i2c_addr = _addr;

  Wire.begin();

  Wire.beginTransmission(i2c_addr);
  Wire.write(0x21);  // turn on oscillator
  Wire.endTransmission();
  blinkRate(HT16K33_BLINK_OFF);

  setBrightness(15); // max brightness
}

void Adafruit_LEDBackpack::writeDisplay(void)
{
  Wire.beginTransmission(i2c_addr);
  Wire.write((uint8_t)0x00); // start at address $00

  for (uint8_t i=0; i<8; i++)
  {
    Wire.write(displaybuffer[i] & 0xFF);
    Wire.write(displaybuffer[i] >> 8);
  }
  Wire.endTransmission();
}

void Adafruit_LEDBackpack::clear(void)
{
  for (uint8_t i=0; i<8; i++)
  {
    displaybuffer[i] = 0;
  }
}

/******************************* 8x8 MATRIX OBJECT */

Adafruit_8x8matrix::Adafruit_8x8matrix(void)
{
}

void Adafruit_8x8matrix::drawPixel(int16_t x, int16_t y, uint16_t color)
{
  if ((y < 0) || (y >= 8)) return;
  if ((x < 0) || (x >= 8)) return;

 // check rotation, move pixel around if necessary
/*
  switch (getRotation()) {
  case 1:
    _swap_int16_t(x, y);
    x = 8 - x - 1;
    break;
  case 2:
*/
    x = 8 - x - 1;
    y = 8 - y - 1;
/*
    break;
  case 3:
    _swap_int16_t(x, y);
    y = 8 - y - 1;
    break;
  }
*/

  // wrap around the x
  x += 7;
  x %= 8;


  if (color)
  {
    displaybuffer[y] |= 1 << x;
  }
  else
  {
    displaybuffer[y] &= ~(1 << x);
  }
}

// drawBitmap() variant for RAM-resident (not PROGMEM) bitmaps.
void Adafruit_8x8matrix::drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color)
{

  int16_t i, j, byteWidth = (w + 7) / 8;
  uint8_t data;

  for (j=0; j<h; j++)
  {
    for (i=0; i<w; i++ )
    {
      if (i & 7)
      {
        data <<= 1;
      }
      else
      {
        data = bitmap[j * byteWidth + i / 8];
      }

      if (data & 0x80)
      {
        drawPixel(x+i, y+j, color);
      }
    }
  }
}

