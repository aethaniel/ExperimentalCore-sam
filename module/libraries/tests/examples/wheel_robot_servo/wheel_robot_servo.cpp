#include "core_digital.h"
#include "Arduino.h"
#include "Servo.hpp"

/*
 * bt_hc06
 * Take control of the board using JY-MCU/HC06 Bluetooth 2.0 module.
 * Remote control is operated from Android phone using simple opensource application:
 * https://play.google.com/store/apps/details?id=com.gundel.bluecontrol&hl=en
 */

#define HC06_SERIAL SERIAL_PORT_HARDWARE_OPEN1

#define PIN_SERVO_LEFT        (14u)
#define PIN_SERVO_RIGHT       (15u)

Servo servo_left;
Servo servo_right;

static void hc06_init(void)
{
  String s;

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
}

static void servos_init(void)
{
  pinMode(PIN_SERVO_LEFT, OUTPUT);
  servo_left.attach(PIN_SERVO_LEFT);    // attaches the servo connected to pin PIN_SERVO_LEFT to the servo_left object

  pinMode(PIN_SERVO_RIGHT, OUTPUT);
  servo_right.attach(PIN_SERVO_RIGHT);  // attaches the servo connected to pin PIN_SERVO_RIGHT to the servo_right object
}

// the setup function runs once when you press reset or power the board
void setup(void)
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)

  SERIAL_PORT_MONITOR.begin( 115200 ) ; // Output to EDBG Virtual COM Port
  hc06_init();

  servos_init();

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
        servo_left.writeMicroseconds(100); //
        delay(1000);                       // wait for a second
        servo_left.writeMicroseconds(0);   // stop the servo moving
      break;

      case 'R':
        // move robot backward
        digitalWrite(LED_BUILTIN, LOW);
        servo_right.writeMicroseconds(100); //
        delay(1000);                        // wait for a second
        servo_right.writeMicroseconds(0);   // stop the servo moving
      break;

      default:
        SERIAL_PORT_MONITOR.print("Received:");
        SERIAL_PORT_MONITOR.println(c);
    }
  }
}
