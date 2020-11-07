
#include "msp430g2553.h"

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  DCOCTL = 0;
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;
  
  P1SEL |= BIT1 + BIT2;
  P1SEL2 |= BIT1 + BIT2;
  UCA0CTL1 |= UCSSEL_2;
  UCA0BR0 = 104;
  UCA0BR1 = 0;
  
  P1DIR |= BIT0;
  P1OUT &=~ BIT0;
  
  UCA0MCTL = UCBRS0;
  UCA0CTL1 &= ~UCSWRST;
  
  IE2 |= UCA0RXIE;
  
  __bis_SR_register(GIE);
  
  return 0;
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
  while (!(IFG2&UCA0TXIFG));
  if (UCA0RXBUF == 'a')
    P1OUT |= BIT0;
  if (UCA0RXBUF == 'b')
    P1OUT &=~ BIT0; 
  UCA0TXBUF = UCA0RXBUF; 
}
    