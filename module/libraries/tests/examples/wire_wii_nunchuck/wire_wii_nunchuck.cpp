#include <Arduino.h>
#include <stdint.h>

#define NUNCHUCK_BTN_C (0x01u)
#define NUNCHUCK_BTN_Z (0x02u)

int val;

typedef struct _NunchuckData
{
  uint8_t jX;
  uint8_t jY;
  uint8_t accX;
  uint8_t accY;
  uint8_t accZ;
  uint8_t buttons;
} NunchuckData;

static bool NunchuckInitialize(TwoWire& interface)
{
  interface.begin(); // join i2c bus as master
  interface.beginTransmission(0x52);// transmit to device 0x52
    interface.write((uint8_t)0xF0);// sends a zero.
    interface.write((uint8_t)0x55);// sends a zero.
    interface.write((uint8_t)0xFB);// sends a zero.
    interface.write((uint8_t)0x00);// sends a zero.
  interface.endTransmission();// stop transmitting

  return 1;
}

static bool NunchuckReadData(TwoWire& interface, NunchuckData& data)
{
  interface.requestFrom(0x52, 6);

  data.jX =   interface.read();
  data.jY =   interface.read();
  data.accX = interface.read();
  data.accY = interface.read();
  data.accZ = interface.read();
  data.buttons = interface.read();

  data.accZ<<=2;
  data.accZ|=data.buttons>>6;

  data.accY<<=2;
  data.accY|=(data.buttons>>4)&0x3;

  data.accX<<=2;
  data.accX|=(data.buttons>>2)&0x3;

  data.buttons&=0x3;

  SERIAL_PORT_MONITOR.print("Joy : ");
  SERIAL_PORT_MONITOR.print(data.jX);
  SERIAL_PORT_MONITOR.print(", ");
  SERIAL_PORT_MONITOR.print(data.jY);

  SERIAL_PORT_MONITOR.print("\tAcc : ");
  SERIAL_PORT_MONITOR.print(data.accX);
  SERIAL_PORT_MONITOR.print(", ");
  SERIAL_PORT_MONITOR.print(data.accY);
  SERIAL_PORT_MONITOR.print(", ");
  SERIAL_PORT_MONITOR.print(data.accZ);

  SERIAL_PORT_MONITOR.print("\tBtn : ");
  SERIAL_PORT_MONITOR.print(" [");
  SERIAL_PORT_MONITOR.print(data.buttons);
  SERIAL_PORT_MONITOR.print("] ");

  switch(data.buttons)
  {
    case 0x0ul:
      SERIAL_PORT_MONITOR.println("C + Z");
      break;

    case 0x1ul:
      SERIAL_PORT_MONITOR.println("C");
      break;

    case 0x2ul:
      SERIAL_PORT_MONITOR.println("Z");
      break;

    case 0x3ul:
      SERIAL_PORT_MONITOR.println("No key");
      break;

    default:
      break;
  }

  interface.beginTransmission(0x52);// transmit to device 0x52
  interface.write((uint8_t)0x00);// sends a zero.
  interface.endTransmission();// stop transmitting

  return 1;
}

void setup()
{
  SERIAL_PORT_MONITOR.begin( 115200 ) ;
  SERIAL_PORT_MONITOR.println("Inits");

  NunchuckInitialize(Wire);

  SERIAL_PORT_MONITOR.println( "Nunchuck ready" ) ;
  delay(100);
}

void loop()
{
  NunchuckData sensor_data;

  if ( NunchuckReadData(Wire, sensor_data) == 1 )
  {
  }
}
