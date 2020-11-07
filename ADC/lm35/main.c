
#include "msp430g2553.h"
#include "UART.H"

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  DCOCTL = 0;
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;
  
  ADC10CTL0 &=~ ENC;
  ADC10CTL0 |= ADC10ON;
  ADC10CTL1 |= INCH_6 + ADC10SSEL_3;
  ADC10AE0 |= BIT6;
  
  init_uart();
  
  __bis_SR_register(GIE);
  int value;
  float temp;
  while(1)
  {
    ADC10CTL0 |= ENC + ADC10SC;
    while (ADC10CTL1 & ADC10BUSY);
    
    value = ADC10MEM;
    temp = (value*3.3/1023)/0.01;
    UART_Write_Float(temp,2);
    UART_Write_String(" oC");
    UART_Write_Char(10);
    __delay_cycles(500000);
  }
  //return 0;
}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}