#include <Arduino.h>

const uint8_t addressTemp = 0x4Ful;
uint16_t temp = 0;
uint8_t a, b;

// AT30TSE758 Temperature sensor with EEPROM

void setup()
{
  SERIAL_PORT_MONITOR.begin( 115200 );
  SERIAL_PORT_MONITOR.println("Wire init");
  Wire.begin();
}

void loop()
{
  Wire.beginTransmission(addressTemp);
  Wire.write((uint8_t) 0x00);
  Wire.endTransmission();

  delay(100);

  Wire.requestFrom(addressTemp, 2);
  SERIAL_PORT_MONITOR.print((char)13);
  SERIAL_PORT_MONITOR.print("Temperature : ");

  a = Wire.read();
  b = Wire.read();

  temp = b << 7;
  temp |= a;
  temp >>= 7;

  SERIAL_PORT_MONITOR.print(temp);
}
