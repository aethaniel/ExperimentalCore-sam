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
}

// the loop function runs over and over again forever
void loop(void)
{
//  int i;

  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
//  for (i=10000;i>0;i--) __NOP();

  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
//  for (i=10000;i>0;i--) __NOP();
}
