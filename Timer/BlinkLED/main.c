
#include "msp430g2553.h"
int count = 0;
int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  P1DIR |= BIT0;
  TACCR0 = 62500;
  TACTL |= TASSEL_2 + ID_3 + MC_2;   
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;
  TACCTL0 |= CCIE;
  __bis_SR_register(GIE); 


  return 0;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
  count++;
  if (count == 1)
  {
    P1OUT ^= BIT0;
    count = 0;
  }
  
}