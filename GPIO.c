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

void GPIOF_Init(){
	SYSCTL_RCGCGPIO_R |= 0x00000020; // activate Port F
while((SYSCTL_PRGPIO_R&0x00000020) == 0){};
	
GPIO_PORTF_LOCK_R= 0x4C4F434B;	
GPIO_PORTF_CR_R = 0x1F; // allow changes to PF4-0
GPIO_PORTF_AMSEL_R &= ~0x1F;
GPIO_PORTF_PCTL_R &= 0x00000;
GPIO_PORTF_AFSEL_R &= ~0x1F;
GPIO_PORTF_DIR_R |= 0x0E; // PF4,PF0 in, PF3-1 out
GPIO_PORTF_PUR_R = 0x11; // pull-up on PF0 and PF4
GPIO_PORTF_DEN_R = 0x1F; // digital I/O on PF4-0
	
}

unsigned char GPIO_getSwitchValue (unsigned char sw){
switch(sw){
	case GPIO_SW1 :return GET_BIT(GPIO_PORTF_DATA_R,4); break;
	case GPIO_SW2 :return GET_BIT(GPIO_PORTF_DATA_R,0); break;
	default :return 0;
}

}
	
void setLedValue(unsigned char ledColor, unsigned char ledState){
switch(ledColor){
	case GPIO_RED_LED: switch(ledState){
		case GPIO_LED_OFF: CLR_BIT(GPIO_PORTF_DATA_R,1);break;
		case GPIO_LED_ON:SET_BIT(GPIO_PORTF_DATA_R,1);break;
		default :break;
	} break;
	case GPIO_BLUE_LED: switch(ledState){
		case GPIO_LED_OFF: CLR_BIT(GPIO_PORTF_DATA_R,2);break;
		case GPIO_LED_ON:SET_BIT(GPIO_PORTF_DATA_R,2);break;
		default :break;
	} break;
	case GPIO_GREEN_LED: switch(ledState){
		case GPIO_LED_OFF: CLR_BIT(GPIO_PORTF_DATA_R,3);break;
		case GPIO_LED_ON:SET_BIT(GPIO_PORTF_DATA_R,3);break;
		default :break;
	} break;
		default:break;
}
}

void GPIOA_Init () {
  SET_BIT(SYSCTL_RCGCGPIO_R,1);
  while(GET_BIT(SYSCTL_PRGPIO_R,1)==0);   
  GPIO_PORTA_CR_R |= 0xFF;              
  GPIO_PORTA_AMSEL_R &= 0x0;        
  GPIO_PORTA_PCTL_R &= 0x0;   
  GPIO_PORTA_DIR_R |= 0xFF;           
  GPIO_PORTA_AFSEL_R &= 0x00;                   
  GPIO_PORTA_DEN_R |= 0xFF;                 
}

void GPIOD_Init () {
  SET_BIT(SYSCTL_RCGCGPIO_R,1);
  while(GET_BIT(SYSCTL_PRGPIO_R,1)==0);   
  GPIO_PORTD_CR_R |= 0xFF;              
  GPIO_PORTD_AMSEL_R &= 0x0;        
  GPIO_PORTD_PCTL_R &= 0x0;   
  GPIO_PORTD_DIR_R |= 0xFF;           
  GPIO_PORTD_AFSEL_R &= 0x00;                   
  GPIO_PORTD_DEN_R |= 0xFF;                 
}
