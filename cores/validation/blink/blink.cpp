#include "core_digital.h"
#include "Arduino.h"

/*
 * Blink
 * Turns on an LED on for one second, then off for one second, repeatedly.
 *
 * Most boards have an on-board LED you can control which is attached to digital pin LED_BUILTIN.
 */

// the setup function runs once when you press reset or power the board
void setup(void)
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

#ifdef SERIAL_PORT_MONITOR
  SERIAL_PORT_MONITOR.begin( 115200 ) ; // Output to EDBG Virtual COM Port
#endif // SERIAL_PORT_MONITOR
#ifdef SERIAL_PORT_HARDWARE_OPEN
  SERIAL_PORT_HARDWARE_OPEN.begin( 57600 ) ;
#endif // SERIAL_PORT_HARDWARE_OPEN

  // Test SERIAL_PORT_MONITOR output
#ifdef SERIAL_PORT_MONITOR
  SERIAL_PORT_MONITOR.write( '-' ) ;   // send a char
  SERIAL_PORT_MONITOR.write( "test1\n" ) ;   // send a string
  SERIAL_PORT_MONITOR.write( "test2" ) ;   // send another string
#endif // SERIAL_PORT_MONITOR

  // Test SERIAL_PORT_HARDWARE_OPEN output
#ifdef SERIAL_PORT_HARDWARE_OPEN
  SERIAL_PORT_HARDWARE_OPEN.write( '-' ) ;   // send a char
  SERIAL_PORT_HARDWARE_OPEN.write( "test1\n" ) ;   // send a string
  SERIAL_PORT_HARDWARE_OPEN.write( "test2" ) ;   // send another string
#endif // SERIAL_PORT_HARDWARE_OPEN
}

// the loop function runs over and over again forever
void loop(void)
{
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second

#ifdef SERIAL_PORT_MONITOR
  SERIAL_PORT_MONITOR.write( '+' ) ;   // send a char
#endif // SERIAL_PORT_MONITOR

  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second

#ifdef SERIAL_PORT_HARDWARE_OPEN
  SERIAL_PORT_HARDWARE_OPEN.write( '+' ) ;   // send a char
#endif // SERIAL_PORT_HARDWARE_OPEN

}
