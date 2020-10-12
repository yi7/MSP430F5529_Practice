#include <msp430.h>
#include "tm1637.h"

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	tm1637_init();

	while(1)
	{
	    tm1637_testWrite(2, 3, 5, 9);
	    //tm1637_display(1, 1);
	    //tm1637_display(2, 2);
	    //tm1637_display(3, 3);
	}


	return 0;
}
