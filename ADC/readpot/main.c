
#include "msp430g2553.h"
#include "UART.H"

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  ADC10CTL0 = ADC10ON;
  ADC10CTL1 = INCH_4;
  ADC10AE0 |= BIT4;
  
  DCOCTL = 0;
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;
  
  P1SEL |= BIT1 + BIT2;
  P1SEL2 |= BIT1 + BIT2;
  UCA0CTL1 |= UCSSEL_2;
  UCA0BR0 = 104;
  UCA0BR1 = 0;
  
  UCA0MCTL = UCBRS0;
  UCA0CTL1 &= ~UCSWRST;
  
  //IE2 |= UCA0RXIE;
  P2DIR |= BIT3 + BIT4 + BIT5;
  
  int value;
  while(1)
  {
    ADC10CTL0 |= ENC + ADC10SC;
    value = ADC10MEM;
    UART_Write_String("Value=  ");
    UART_Write_Int(value);
    UART_Write_Char(10);
  }
  //return 0;
}
