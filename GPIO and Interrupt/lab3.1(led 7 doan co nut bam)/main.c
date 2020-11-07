
#include "msp430g2553.h"
int led7seg[11]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
int check=0;
void quetled(void);
int hc, hdv;
int k=0;
int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  P1DIR |= (BIT3 + BIT4);
  P2DIR = 0xFF;
  P2SEL &=~ (BIT6 + BIT7);
  P2SEL2 &=~ (BIT6 + BIT7);

  P1DIR &=~ (BIT5 + BIT7);
  P1IE |= (BIT5 + BIT7);
  P1IES |= (BIT5 + BIT7);
  P1IFG &=~ (BIT5 + BIT7);
 
 
  __bis_SR_register(GIE);
  
  while (1)
  {
    
    if (check == 1)
    {
       if (k==99)
        k=0; else k++;
      hdv = k%10;
      hc = k/10;
     check =0;
    }
     if (check == 2)
    {
       if (k==0)
        k=99;
       else k--;
      hdv = k%10;
      hc = k/10;
     check =0;
    }
    quetled();
    
  }
  //return 0;
}

void quetled(void)
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

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  
  if (P1IFG&BIT5)
    check = 1;
  if (P1IFG&BIT7)
    check = 2;
  P1IFG &=~ (BIT5 + BIT7);
}
