
#include "msp430g2553.h"
int led7seg[11]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  P1DIR |= (BIT3 + BIT4);
  P2DIR = 0xFF;
  P2SEL &=~ (BIT6 + BIT7);
  P2SEL2 &=~ (BIT6 + BIT7);
  //P1OUT &=~ (BIT3 + BIT4);
  P2OUT = 0x00;
   int k=0;
  int hc, hdv;
  while (1)
  {
    /*
    for (int i=0;i<10;i++)
    {
      P2OUT = led7seg[i];
      __delay_cycles(500000);
    }
    */
    for (int i=0; i<10;i++)
    {
      P1OUT &=~ BIT4;
      P1OUT |= BIT3;
      P2OUT = led7seg[hdv];
      __delay_cycles(5000);
    
      P1OUT &=~ BIT3;
      P1OUT |= BIT4;
      P2OUT = led7seg[hc];
      __delay_cycles(5000);
    }
     
      k++;
      hdv = k%10;
      hc = k/10;
    if (k==99)
      k=0;
    
  }
  //return 0;
}

