#include "../../Include/MCAL/tm4c123gh6pm.h"
#include <string.h>
#include <stdint.h>
#define GET_REG(reg)        (reg&0xff)


void UART_Init(void ){
	
	
	
	SYSCTL_RCGCUART_R |=0x0001 ;//activate porta 
	while((SYSCTL_PRUART_R    & 0x01) == 0){};
	SYSCTL_RCGCGPIO_R |=0x0001 ;// to activate port A

	UART0_CTL_R &=~0x0001; //disabling uart 
	//*****************************
	
	UART0_IBRD_R=104 ;
	UART0_FBRD_R=11 ;
	//*****************************
	
	UART0_LCRH_R=0x0070; //8-bit word length , enable FIFO 
	UART0_CTL_R=0x0301; // enable UARTEN ,TXE,RXE 
	GPIO_PORTA_AFSEL_R |= 0x03 ;// enable alternate function	in pA0,PA1
	GPIO_PORTA_PCTL_R= (GPIO_PORTA_PCTL_R&0xFFFFFF00)|0x00000011;//choose the UART function 
	
	GPIO_PORTA_DEN_R |= 0x03 ; // enable digital I/O on PA0,PA1
	GPIO_PORTA_AMSEL_R &=~ 0x03 ;//disable analog function on PA0,PA1 
}




char UART_InChar(void){
		while(((UART0_FR_R &0x10)!= 0 )) ;//block the program until input is recieved 
		return (char)( UART0_DR_R & 0xFF ) ;
}
 char UART_GetChar (){
  while ((UART0_FR_R & UART_FR_RXFE)!=0);
	 return (char) GET_REG(UART0_DR_R);
 }
void UART_OutChar(char data){
		while((UART0_FR_R & 0x0020)!=0);// check if the buffer is empty 
		UART0_DR_R=data ;
}
void UART_outString(char *pt){
		while(*pt){
			UART_OutChar(*pt) ;
			pt++ ;
		}
		
}



 void getCommandd(char *command , int len ){ 
		char character ;
		int i ;
		for(i=0 ; i<len ; i++){
				character=UART_InChar();
				if( character!='\r'){
						command[i]=character ;
						UART_OutChar(command[i]) ;
				}else if (character=='\r' || i==len ){
						break ;
				}
				
		}
	
}

 void getCommand(char *command , char stopchar ){ 
		char character [1] ;
		int i = 0  ;
		while(1){
				getCommandd(character,1);
				if( character[0]!=stopchar){
						command[i]=character[0] ;
					  i++ ;
						//UART_OutChar(command[i]) ;
				}else if (character[0]==stopchar ){
						break ;
				}
				
		}
	
}
 
