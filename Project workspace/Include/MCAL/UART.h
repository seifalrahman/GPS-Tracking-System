#ifndef UART_H
#define UART_H



void UART_Init(void );
char UART_InChar(void);
char UART_GetChar ();
void UART_OutChar(char data);
void UART_outString(char *pt);
void getCommandd(char *command , int len );

extern char lat [20]={0} ;
extern char longi [20]={0} ;
extern char speedd [10]={0} ;

#endif
