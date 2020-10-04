#include <msp430.h>

unsigned int OFCount;

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A_CCR0_ISR(void)
{
    OFCount++;
}

void delay(int msecs)
{
    OFCount = 0;
    TA0CCR0 = 1000 - 1; //Start Timer, Compare value for Up Mode to get 1ms delay per loop

    while(OFCount <= msecs);

    TA0CCR0 = 0;
}

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer

    P1DIR |= 0x01; //Set P1.0 to output direction
    __bis_SR_register(GIE); //Enable Interrupts

    TA0CTL |= TASSEL_2; //Set to SMCLK timer
    TA0CTL |= ID_0; //ID /1
    TA0EX0 |= TAIDEX_0; //IDEX /1
    //TA0CTL |= TAIE; //Timer interrupts on overflow
    TA0CTL |= MC_1; //Set timer to Up mode

    TA0CCR0 = 0; //Initially stop the timer
    TA0CCTL0 |= CCIE; //Enabled interrupt for CCR0

    while(1)
    {
        P1OUT ^= 0x01;
        delay(500);

        P1OUT ^= 0x01;
        delay(2000);
    }
}
