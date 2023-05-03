#include "D:\keil 4\tm4c123gh6pm.h"
#include "D:\keil 4\bit_utilies.h"
#include "GPIO.h"

void GPIOB_Init () {
  SET_BIT(SYSCTL_RCGCGPIO_R,1);
  while(GET_BIT(SYSCTL_PRGPIO,1)==0);   
  GPIO_PORTB_CR_R |= 0xFF;              
  GPIO_PORTB_AMSEL_R &= 0x0;        
  GPIO_PORTB_PCTL_R &= 0x0;   
  GPIO_PORTB_DIR_R |= 0xFF;           
  GPIO_PORTB_AFSEL_R &= 0x00;                   
  GPIO_PORTB_DEN_R |= 0xFF;                 
}
/*void GPIO_PORTB_set (unsigned char Value){
	
	GPIO_PORTB_DATA_R= Value;
}*/
