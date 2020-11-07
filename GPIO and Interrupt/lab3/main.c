
#include "msp430g2553.h"
void sangkotat(void);
void sangtat(void);
void nhapnhay(void);
void sanghet(void);
int check;
int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  P2DIR = 0xFF;
  P2SEL &=~ (BIT6 + BIT7);
  P2SEL2 &=~ (BIT6 + BIT7);
  P1DIR &=~ (BIT3 + BIT4 + BIT5 + BIT6);
  P1IE |=  (BIT3 + BIT4 + BIT5 + BIT6);
  P1IES |= (BIT3 + BIT4 + BIT5 + BIT6);
  P1IFG &=~ (BIT3 + BIT4 + BIT5 + BIT6);
  P2OUT = 0x00;
  __bis_SR_register(GIE);
  while(1)
  {
    if (check == 4)
      sanghet();
    else if (check == 2)
      nhapnhay();
    else if (check == 3)
      sangkotat();
    else if (check==1)
      sangtat();
  }
      
}

void sangkotat(void)
{
  P2OUT |= BIT0;
  for (int i=0;i<8;i++)
  {
    __delay_cycles(50000);
    P2OUT=P2OUT <<1;
    P2OUT++;
  }
  P2OUT = 0x00;
}

void sangtat(void)
{
  P2OUT = 0x00;
  P2OUT |= BIT0;
  for (int i=0;i<8;i++)
  {
    __delay_cycles(50000);
    P2OUT=P2OUT <<1;
  }
  P2OUT = 0x00;
}

void sanghet(void)
{
  P2OUT = 0xFF;
}

void nhapnhay(void)
{
    P2OUT ^= 0xFF;
    __delay_cycles(50000);
  
}
   
#pragma vector=PORT1_VECTOR
__interrupt void PORT_1(void)
{
  __delay_cycles(1000);
  if(P1IFG&BIT3)
    check = 1;
  else if(P1IFG&BIT4)
    check = 2;
  else if(P1IFG&BIT5)
    check = 3;
  else if(P1IFG&BIT6)
    check = 4;
  
  P1IFG &=~ (BIT3 + BIT4 + BIT5 + BIT6);
}