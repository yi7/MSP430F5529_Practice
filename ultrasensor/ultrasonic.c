#include "ultrasonic.h"

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A_CCR0_ISR(void)
{
    cycle_counter++;
}

#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void)
{
    if(P1IFG & PIN) //Check if interrupt
    {
        if(!(P1IES & PIN)) //Check if rising edge
        {
            TA0CTL |= TACLR; //Clear timer A
            cycle_counter = 0;
            P1IES |= PIN; //Set to falling edge
        }
        else
        {
            sensor = (long)cycle_counter * 1000 + (long)TA0R;
        }
        P1IFG &= ~PIN; //Clear flag
    }
}

void ultrasonic_init()
{
    __bis_SR_register(GIE); //Enable interrupts
    TA0CTL |= TASSEL_2; //Set to SMCLK timer
    TA0CTL |= MC_1; //Set timer to up mode
    TA0CTL |= ID_0; //ID /1
    TA0EX0 |= TAIDEX_0; //IDEX /1

    TA0CCTL0 |= CCIE; //Enable interrupt for CCR0
    TA0CCR0 = 1000; //1ms at 1mhz

    P1DIR |= 0x01; //Set P1.0 as output for testing purpose
}

long ultrasonic_pulse()
{
    P1IFG &= ~PIN; //Clear interrupt flag
    P1IE |= PIN; //Enable interrupt
    P1IES &= ~PIN; //Set interrupt edge to rising
    __delay_cycles(30000); //Delay for 30ms, pin times out if no object detected
    //ultrasonic_delay(20);
    return sensor;
}

long ultrasonic_getDistance()
{
    P1DIR |= PIN;
    P1OUT &= ~PIN;
    __delay_cycles(2);
    P1OUT |= PIN;
    __delay_cycles(5);
    P1OUT &= ~PIN;
    P1DIR &= ~PIN;
    long duration;
    duration = ultrasonic_pulse();
    return duration / 58; //Return in cm
}

