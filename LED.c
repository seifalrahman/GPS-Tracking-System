#include "tm4c123gh6pm.h"
#include "bit_utilities.h"
#include "LED.h"

//Initializes the LEDS to be digital output and zero
void LED_Setup(){
	SYSCTL_RCGCGPIO_R |= 0x20;
	while(~(SYSCTL_RCGCGPIO_R &= 0x20));
	GPIO_PORTF_LOCK_R= 0x4C4F434B;
	GPIO_PORTF_CR_R= 0xFF; // or GPIO_PORTF_CR_R= 0x01; u never know
	GPIO_PORTF_AMSEL_R &= ~0x0E;
	GPIO_PORTF_DEN_R |= 0x0E;
	GPIO_PORTF_DIR_R |= 0x0E;
	GPIO_PORTF_PCTL_R &= 0xF000F;
	GPIO_PORTF_AFSEL_R &= ~0x0E;
	GPIO_PORTF_DATA_R &= ~0x0E;
}
//Should be called in main at the start of the program after GPS_GetDistance
void LED_Start(float distance){
	if(distance<=0.5){
		//Green LED should be lit
		GPIO_PORTF_DATA_R &= 0x08;
	}
	if(distance<5 || distance>0.5){
		//Yellow LED should be lit (there is no yellow LED)
		GPIO_PORTF_DATA_R &= 0x0A;
	}
	if(distance>=5){
		//Red LED should be lit
		GPIO_PORTF_DATA_R &=0x02;
	}
}
