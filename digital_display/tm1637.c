#include "tm1637.h"

void tm1637_init()
{
    P2DIR |= CLK; //Set P2.4 as output
    P1DIR |= DIO; //Set P1.5 as output

    tm1637_start();
    tm1637_writeValue(0x8c); //0x88 + 4
    tm1637_stop();

    tm1637_writeAll(0x00, 0x00, 0x00, 0x00);
}

void tm1637_start()
{
    P2OUT |= CLK;
    P1OUT |= DIO;
    P1OUT &= ~DIO;
    P2OUT &= ~CLK;
}

void tm1637_stop()
{
    P2OUT &= ~CLK;
    P1OUT &= ~DIO;
    P2OUT |= CLK;
    P1OUT |= DIO;
}

void tm1637_writeOne(uint8_t col, uint8_t value)
{
    tm1637_start();
    tm1637_writeValue(ADDR_FIXED);
    tm1637_stop();

    tm1637_start();
    tm1637_writeValue(ADDR_START | col);
    tm1637_writeValue(hex_table[value]);
    tm1637_stop();
}

void tm1637_writeAll(uint8_t first, uint8_t second, uint8_t third, uint8_t fourth)
{
    tm1637_start();
    tm1637_writeValue(ADDR_AUTO);
    tm1637_stop();

    tm1637_start();
    tm1637_writeValue(ADDR_START);
    tm1637_writeValue(hex_table[first]);
    tm1637_writeValue(hex_table[second]);
    tm1637_writeValue(hex_table[third]);
    tm1637_writeValue(hex_table[fourth]);
    tm1637_stop();
}

void tm1637_writeValue(uint8_t value)
{
    uint8_t i;
    for(i = 0; i < 8; i++)
    {
        P2OUT &= ~CLK;
        if(value & 0x01)
        {
            P1OUT |= DIO;
        }
        else
        {
            P1OUT &= ~DIO;
        }
        value >>= 1;
        P2OUT |= CLK;
    }

    P2OUT &= ~CLK;
    P1DIR &= ~DIO;
    P2OUT |= CLK;
    P1DIR |= DIO;
}


