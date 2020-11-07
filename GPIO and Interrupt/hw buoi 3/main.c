
#include "msp430g2553.h"

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  P1DIR |= BIT6;
  P1DIR &=~ BIT3;
  P1REN |= BIT3;
  P1OUT |= BIT3;
  
  P1OUT &=~ BIT6;
  
  while (1)
  {
    if ((P1IN&BIT3)==0)
    {
      for (int i=0; i<6; i++)  
      //Vi o day em dung toggle nen phai chay 6 vong lap de trang thai cuoi cung cua led la off
      {
        P1OUT ^= BIT6;
        __delay_cycles(1000000);
      }
      /*
      for (int i=0; i<3; i++) 
      {
        P1OUT |= BIT6;
        __delay_cycles(1000000);
        P1OUT &=~ BIT6;
        __delay_cycles(1000000);
      }
      */
    }
  }
  
  //return 0;
}
