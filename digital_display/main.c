#include <msp430.h>
#include "tm1637.h"

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	tm1637_init();

	while(1)
	{
	    //tm1637_writeAll(0, 7, 3, 4);

	    tm1637_writeOne(0, 1);
	    tm1637_writeOne(1, 3);
	    tm1637_writeOne(2, 5);
	    tm1637_writeOne(3, 7);
	}


	return 0;
}
