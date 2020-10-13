#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include <stdint.h>
#include <msp430.h>

#define PIN 0x10 //P1.4
#define TRIG 0x08 //P1.3

unsigned int cycle_counter;
long sensor;

void ultrasonic_init();
long ultrasonic_pulse();
long ultrasonic_getDistance();

#endif /* ULTRASONIC_H_ */
