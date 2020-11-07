
#include "msp430g2553.h"
void blinkLED();
int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  P1DIR |= BIT6;
  P1DIR &=~ BIT3;
  P1REN |= BIT3;
  P1OUT |= BIT3;
  P1IE |= BIT3;
  P1IES |= BIT3;
  P1IFG &=~ BIT3;
  
  while (1)
  {
    P1OUT ^= BIT6;
    __delay_cycles(1000000);
    if((P1IN&BIT3)==0)
    {
      __bis_SR_register(GIE);
    }
  }
  //return 0;
}

void blinkLED()
{
  for(int i=0; i<20; i++)
  {
    P1OUT ^= BIT6;
    __delay_cycles(250000);
  }
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  blinkLED();
  P1IFG &=~ BIT3;
}