#include  <msp430g2553.h>
unsigned int i = 0;                         
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 
  P1DIR |= 0x01;                            
  for (;;)                                  
  {
    P1OUT ^= 0x01;                         
    for(i=0; i< 20000; i++);               
   }
}
