
#include "msp430g2553.h"

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  P1DIR |= BIT0+BIT6;
  P1DIR &=~ BIT3;
  P1REN |= BIT3;
  P1OUT |= BIT3;
  P1OUT |= BIT0+BIT6;
  while (1)
  {
    if((P1IN&BIT3)==0)
    {
      while ((P1IN&BIT3)==0);
      P1OUT ^= BIT0+BIT6;
      //__delay_cycles(1000000);
    }
    //__delay_cycles(100000);
  }
  
  //return 0;
}
