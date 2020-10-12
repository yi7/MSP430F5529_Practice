#include "tm1637.h"

void tm1637_init()
{
    P2DIR |= CLK; //Set P2.4 as output
    P1DIR |= DIO; //Set P1.5 as output

    tm1637_start();
    tm1637_write(0x8c); //0x88 + 4
    tm1637_stop();

    tm1637_testWrite(0x00, 0x00, 0x00, 0x00);
}


void tm1637_clear()
{
    tm1637_display(0x00,0x7f);
    //tm1637_display(0x01,0x7f);
    //tm1637_display(0x02,0x7f);
    //tm1637_display(0x03,0x7f);
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

void tm1637_write(int8_t data)
{
    uint8_t i, count1;
    for(i = 0; i < 8; i++)
    {
        P2OUT &= ~CLK;
        if(data & 0x01)
        {
            P1OUT |= DIO;
        }
        else
        {
            P1OUT &= ~DIO;
        }

        data >>= 1;
        P2OUT |= CLK;
    }

    P2OUT &= ~CLK;
    P1OUT |= DIO;
    P2OUT |= CLK;
    P1DIR &= ~DIO;
    while(P1DIR & DIO)
    {
        count1 += 1;
        if(count1 == 200)
        {
            P1DIR |= DIO;
            P1OUT &= ~DIO;
            count1 = 0;
        }
        P1DIR &= ~DIO;
    }
    P1DIR |= DIO;
}

void tm1637_testWrite(uint8_t first, uint8_t second, uint8_t third, uint8_t fourth)
{
    tm1637_start();
    tm1637_testValue(0x40);
    tm1637_stop();

    tm1637_start();
    tm1637_testValue(0xc0);
    tm1637_testValue(hex_table[first]);
    tm1637_testValue(hex_table[second]);
    tm1637_testValue(hex_table[third]);
    tm1637_testValue(hex_table[fourth]);
    tm1637_stop();
}

void tm1637_testValue(uint8_t value)
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

void tm1637_display(uint8_t col, int8_t val)
{
    int8_t seg_data;
    seg_data = tm1637_coding(val);
    tm1637_start();
    tm1637_write(brightness);
    tm1637_stop();
    tm1637_start();
    tm1637_write(ADDR_FIXED);
    tm1637_stop();
    tm1637_start();
    tm1637_write(col | 0xc0);
    tm1637_write(seg_data);
    tm1637_stop();

}

uint8_t tm1637_coding(uint8_t data)
{
      if(data == 0x7f)
      {
          data = 0x00;
      }
      else
      {
          data = hex_table[data];
      }
      return data;
}


