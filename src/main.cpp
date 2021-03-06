/*
 * This is the routine for the electronic compass.
 * The ATMega32U4 will be initialized making sure to
 * unmask interrupts for the I2C bus and the necessary
 * GPIO interrupts for the magnetometer/accelerometer
 * and LCD display respectively. From here we simply
 * take readings from the sensor package, and map the
 * results to display values for the LCD.
 */

#include <avr/io.h>
#include <util/delay.h>
#include "LSM303DLH/LSM303DLH.h"
#include "PCD8544/PCD8544.h"

int main()
{
  PCD8544 display;
  LSM303DLH compass;

  // Initialize all unused GPIO pins to output LOW
  DDRD = 0xFF;
  DDRF = 0x00;
  PORTD = 0xFF;
  PORTF = 0x00;

  // Set PB0 (SS) as an output HIGH
  DDRB |= (1<<PB0);
  PORTB |= (1<<PB0);

  //Power on the display backlight
  DDRB |= (1<<PB6);
  PORTB |= (1<<PB6);

  //Initialize the LSM303 and the Nokia5110
  display.InitPCD8544();
  compass.InitLSM303DLH();

  while(true)
    display.DisplayHeading(compass.ReadHeading());

  return 0;
}
