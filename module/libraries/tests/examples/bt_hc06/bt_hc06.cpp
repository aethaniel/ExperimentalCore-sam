#include "core_digital.h"
#include "Arduino.h"

/*
 * bt_hc06
 * Take control of the board using JY-MCU/HC06 Bluetooth 2.0 module.
 * Remote control is operated from Android phone using simple opensource application:
 * https://play.google.com/store/apps/details?id=com.gundel.bluecontrol&hl=en
 */

#define HC06_SERIAL SERIAL_PORT_HARDWARE_OPEN1

// the setup function runs once when you press reset or power the board
void setup(void)
{
  String s;

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)

  SERIAL_PORT_MONITOR.begin( 115200 ) ; // Output to EDBG Virtual COM Port
  HC06_SERIAL.begin( 9600 ) ; // Default baudrate for HC06 module

  // Test SERIAL_PORT_MONITOR output
  SERIAL_PORT_MONITOR.println("AT");
  HC06_SERIAL.print("AT");
  s=HC06_SERIAL.readString();
  SERIAL_PORT_MONITOR.println(s);

  SERIAL_PORT_MONITOR.println("AT+VERSION");
  HC06_SERIAL.print("AT+VERSION");
  s=HC06_SERIAL.readString();
  SERIAL_PORT_MONITOR.println(s);

  SERIAL_PORT_MONITOR.println("AT+NAMESAM_HC06");
  HC06_SERIAL.print("AT+NAMESAM_HC06");
  s=HC06_SERIAL.readString();
  SERIAL_PORT_MONITOR.println(s);

  delay(1000);              // wait for a second
  // Show we did the setup already
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED off
}

// the loop function runs over and over again forever
void loop(void)
{
  char c;

  if ( HC06_SERIAL.available() )
  // if text arrived in from BT serial...
  {
    c=HC06_SERIAL.read();
    switch ( c )
    {
      case 'U':
        // move robot forward
        digitalWrite(LED_BUILTIN, HIGH);
      break;

      case 'D':
        // move robot backward
        digitalWrite(LED_BUILTIN, LOW);
      break;

      case 'L':
        // move robot forward
        digitalWrite(LED_BUILTIN, HIGH);
      break;

      case 'R':
        // move robot backward
        digitalWrite(LED_BUILTIN, LOW);
      break;

      default:
        SERIAL_PORT_MONITOR.print("Received:");
        SERIAL_PORT_MONITOR.println(c);
    }
  }
}
