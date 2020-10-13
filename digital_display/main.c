#include <msp430.h>
#include "tm1637.h"
#include "ultrasonic.h"
#include <stdio.h>

int8_t bits[4] = {0};

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	tm1637_init();
	ultrasonic_init();

	P4DIR |= BIT7;
	P4OUT |= BIT7;

	int distance = 0;
	int i;
	while(1)
	{
	    //tm1637_writeAll(0, 7, 3, 4);

	    //tm1637_writeOne(0, 0);
	    //tm1637_writeOne(1, 7);
	    //tm1637_writeOne(2, 3);
	    //tm1637_writeOne(3, 4);
	    distance = ultrasonic_getDistance();
        memset(bits, 0, 4);

        for(i = 3; i >= 0; i--)
        {
            bits[i] = distance % 10;
            distance = distance / 10;
            tm1637_writeOne(i, bits[i]);
        }
        //ultrasonic_delay(100);
        __delay_cycles(50000);
        __delay_cycles(50000);
	}

	return 0;
}
