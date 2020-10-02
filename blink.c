#include <msp430.h>

/**
 * blink.c
 */
void main(void)
{
    /*
    unsigned int i; //delay variable

    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer

    P1REN |= 0x02; // Enable resistor on P1.1
    P1OUT  = 0x02; // Set resistor to pull-up, P1.0 low
    P1DIR  = 0x01; // Set P1.0 as output and P1.1 as input
    P4OUT  = 0x80; // Set P4.7 high
    P4DIR  = 0x80; // Set P4.7 as output

    //P1REN |= 0x01;
    //P1OUT |= 0x01;
    //P1DIR |= 0x01;
    //P4OUT |= 0x01;
    //P4DIR |= 0x01;

    while( 1 )
    {
        if( !(P1IN & 0x02) ) // If push button is pressed
        {
            P1OUT ^= 0x01;
            P4OUT ^= 0x80;

            //for( i=0; i<30000; i++ );
        }
    }
    */

    /*
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
    P1DIR |= 0x01; //Set P1.0 to output direction

    for(;;)
    {
        volatile unsigned int i; //Volatile to prevent optimization
        P1OUT ^= 0x01;
        //for( i=0; i<30000; i++ );
        __delay_cycles(40000);
    }


    return 0;
    */


    WDTCTL = WDTPW | WDTHOLD;
    P1DIR = 0x01;
    P1REN = 0x02;
    P1OUT = 0x02;

    while(1)
    {
        if( !(P1IN & 0x02) )
        {
            P1OUT |= 0x01;
        }
        else
        {
            P1OUT = 0x02;
        }
    }


}
