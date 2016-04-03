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

#include <Arduino.h>

#if WIRE_INTERFACES_COUNT > 0

// AT30TSE758 Temperature sensor with EEPROM

#define I2C_TEMP_SENSOR_ADDRESS            ((uint8_t)0x4Ful)
#define AT30TSE75x_REG_ADDR_TEMPERATURE    ((uint8_t)0x00u)

uint16_t temperatureValue = 0x0000;
float temperatureCelsius = 0.0f;
int ledState = LOW; // ledState used to set the LED

void setup(void)
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  SERIAL_PORT_MONITOR.begin(115200);
  SERIAL_PORT_MONITOR.println("Wire init");
  Wire.begin();
}

void loop(void)
{
  ledState^=HIGH;

  digitalWrite(LED_BUILTIN, ledState);   // turn the LED on (HIGH is the voltage level)

  Wire.beginTransmission(I2C_TEMP_SENSOR_ADDRESS);
  Wire.write(AT30TSE75x_REG_ADDR_TEMPERATURE); // Request temperature value
  Wire.endTransmission();

  delay(100);

  Wire.requestFrom((uint8_t)I2C_TEMP_SENSOR_ADDRESS, (uint8_t)2);

  temperatureValue = Wire.read()<<8;
  temperatureValue |= Wire.read();

  if ((temperatureValue & 0x8000) == 0)
  {
    temperatureCelsius = (temperatureValue>>8) + ((temperatureValue&0x00F0)>>4)*0.0625f;
  }
  else
  {
    uint16_t twosComplement = (~temperatureValue) + 1;
    temperatureCelsius = - (twosComplement>>8) - ((twosComplement & 0x00F0)>>4)*0.0625f;
  }

  SERIAL_PORT_MONITOR.print("Temperature : ");
  SERIAL_PORT_MONITOR.print(temperatureValue);
  SERIAL_PORT_MONITOR.print(", ");
  SERIAL_PORT_MONITOR.print(temperatureCelsius);
  SERIAL_PORT_MONITOR.println("C");

  delay(1000);
}

#else

void setup(void)
{
}

void loop(void)
{
}

#endif //WIRE_INTERFACES_COUNT > 0
