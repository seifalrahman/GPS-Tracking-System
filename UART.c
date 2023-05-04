#include "UART.h"
 
 void UART_Init(void ){
	
	 SET_BIT(SYSCTL_RCGCUART_R,0);
	 while(GET_BIT(SYSCTL_PRUART_R,0)==0);
	 SET_BIT(SYSCTL_RCGCGPIO_R,0);
	 while(GET_BIT(SYSCTL_PRGPIO_R,0)==0);
	 CLR(UART0_CTL_R,UART_CTL_UARTEN);
	 UART0_IBRD_R=104;
	 UART0_FBRD_R=11;
	 SET(UART0_LCRH_R,UART_LCRH_WLEN_8);
	 SET(UART0_LCRH_R,UART_LCRH_FEN);
	 //enable uart,txe,rxe 
	 SET(UART0_CTL_R,UART_CTL_UARTEN);
	 SET(UART0_CTL_R,UART_CTL_TXE);
	 SET(UART0_CTL_R,UART_CTL_RXE);
}
 
 char UART_GetChar (){
  while ((UART0_FR_R & UART_FR_RXFE)!=0);
	 return (char) GET_REG(UART0_DR_R);
 }
 
 char UART_IsCharAvail (){
	return ((UART0_FR_R & UART_FR_RXFE )==UART_FR_RXFE) ;
	 
 }