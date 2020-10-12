#ifndef TM1637_H_
#define TM1637_H_

#include <stdint.h>
#include <msp430.h>

#define CLK 0x10 //P2.4
#define DIO 0x20 //P1.5
#define ADDR_AUTO  0x40
#define ADDR_FIXED 0x44
#define ADDR_START  0xc0

const static uint8_t hex_table[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f}; //0~9

void tm1637_init();
void tm1637_start();
void tm1637_stop();
void tm1637_writeOne(uint8_t col, uint8_t value);
void tm1637_writeAll(uint8_t first, uint8_t second, uint8_t third, uint8_t fourth);
void tm1637_writeValue(uint8_t value);

#endif /* TM1637_H_ */
