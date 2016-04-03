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

#if WIRE_INTERFACES_COUNT > 0

#include <Arduino.h>
#include "Adafruit_LEDBackpack.h"

static const uint8_t smile_bmp[] =
{
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
};

static const uint8_t neutral_bmp[] =
{
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10111101,
  B10000001,
  B01000010,
  B00111100
};
static const uint8_t frown_bmp[] =
{
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10011001,
  B10100101,
  B01000010,
  B00111100
};


Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

void setup(void)
{
  Serial.begin(115200);
  Serial.println("HT16K33 8x8 LED Matrix Test");

  matrix.begin(0x70);  // pass in the address
}


void loop(void)
{
  matrix.clear();      // clear display
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();      // clear display
  matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();      // clear display
  matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();      // clear display
  matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);
}

#else
#include <Arduino.h>

void setup(void)
{
}

void loop(void)
{
}
#endif //WIRE_INTERFACES_COUNT > 0
