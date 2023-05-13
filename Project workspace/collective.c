#include "Include/MCAL/tm4c123gh6pm.h"
#include <string.h>
#include <stdint.h>
#include <math.h> 
#include <stdio.h>
#include <stdlib.h>
#define PI 3.141592653589793238 
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


void RGB_Init(void){ 
	SYSCTL_RCGCGPIO_R|=0x20; //INTIALIZE THE CLOCK OF PORTF 
	while((SYSCTL_PRGPIO_R & 0x20)==0); //delay 
	GPIO_PORTF_LOCK_R = 0x4C4F434B; //unlocking the ports have the same value 
	GPIO_PORTF_CR_R |= 0x0E; //Allow changing pin 3,2,1 in portF 
	GPIO_PORTF_AMSEL_R &=~0x0E; //disable the analog function 
	GPIO_PORTF_PCTL_R &=~0x0000FFF0; 
	GPIO_PORTF_AFSEL_R &=~0x0E; //disable the alternate function 
	GPIO_PORTF_DIR_R |= 0x0E; //Pin1,2,3 is output 
	GPIO_PORTF_DEN_R |=0x0E; 
	GPIO_PORTF_DATA_R &=~0x0E; //intialize pins 1,2,3 to be off 
}

void RGB_setOutput (unsigned char data ){
		GPIO_PORTF_DATA_R |= data ;
}

void  RGB_clearOutput(unsigned char data){
		GPIO_PORTF_DATA_R &=~data ;
}

double GPStoDeg(double val)
{
	return (int)(val / 100) + (val - (int)(val / 100) * 100) / 60.0;
    
} //before lat and long is passet to get_distance 

float ToRad (float angle){
		return angle *PI/180 ;
}

float GPS_getDistance(float currentLong , float currentLat , float destLong , float destLat){
		//Get Radian 
	 float currentLongRad=ToRad(currentLong) ;//phiA
	 float currentLatRad=ToRad(currentLat) ;//phiB
	 float destLongRad = ToRad(destLong) ;//lambdaA
	 float destLatRad=ToRad(destLat) ;//lambdaB
	 //Get Difference 
	 float longDiff = destLongRad- currentLongRad ;
	 float latDiff = destLatRad - currentLatRad ;
	 // calculate Distance 
	 float a = pow (sin(latDiff/2),2) +cos(currentLatRad)*cos(destLatRad)*pow(sin(longDiff/2),2) ; 
		double c = 2*atan2(sqrt(a) , sqrt(1-a) ) ;
	 return 6371000*c ; ///another edit 

 }

char lat [20]={0} ;
 char longi [20]={0} ;
 char speedd [10]={0} ;
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

char GPS_logName[]="$GPRMC,";
char GPS[80] ;
char Valid [1];
char N_or_S [1];
char E_or_W [1];
float currentLong, currentLat,speed ;
double long_final=31.2806451,lat_final=30.0648936; 
void GPS_read2(){
	char counter =0 ;
	char  recievedChar [1];
	char i=0 ;
	char flag =1 ;
	char c [1];
	do{
		getCommandd(c,1);
		while(c[0]!=GPS_logName[i]){
			memset(c,0,1);
			getCommandd(c,1);
		}
		i++;
		}while(i!=7);
	while(1){
			if(flag){
				
				
				getCommandd(recievedChar,1);
				if(recievedChar[0]==','){counter++;}
			}
			switch(counter){
				case 1 : getCommandd(Valid,1); break ;
				case 2 : getCommand(lat,',');counter++;flag=0;break;
				case 3 : getCommandd(N_or_S,1);flag=1;break;
				case 4 : getCommand(longi,',');counter++;flag=0;break;
				case 5 : getCommandd(E_or_W,1);flag=1;break;
				case 6 : getCommand(speedd,',');counter++;flag=0;break;
			
			}
			if(counter==7) break;
	
	}
	if(N_or_S[0]=='N')
						currentLat=atof(lat);
					else
						currentLat=-atof(lat) ;
	if(E_or_W[0]=='E')
						currentLong=atof(longi);
					else
						currentLong=-atof(longi);

}
//IN the main donnot forget to do memset to the arrays and donnot forget checking if it is valid or not and if you used GPS_read2() we will not use gps_read  nor gps_format


int main(void){
		//char str[20];
	
		float distance ;
	
		UART_Init();
	  RGB_Init() ;
	RGB_setOutput (0x8);
	RGB_setOutput (0x2);
	
		/*currentLat=30.063089 ;
		currentLong=31.299038 ;
		distance = GPS_getDistance(currentLong ,currentLat ,long_final ,lat_final) ;
		//sprintf(str, "%f", distance);
		//UART_outString(str);
	  if(distance >5000){
			RGB_setOutput (0x2);
		}else if ((distance<5000 && distance >1000)){
			RGB_setOutput (0x4);
		}else if (distance <1000){
			RGB_setOutput (0x8);
		}*/
GPS_read2() ;
long_final=currentLong ;
lat_final= currentLat;


	while(1){
				memset(lat,0,20);
				memset(longi,0,20);
			  memset(speedd,0,20);
				//UART_outString("Enter:\n") ;
				GPS_read2() ;
		RGB_clearOutput(0xE);
			  RGB_setOutput (0x8);
		   
				//UART_outString("lat  is ") ;
			
				//UART_outString(lat);
				//UART_outString("\n") ;
			//	UART_outString("long  is ") ;
				//UART_outString(longi);
				//UART_outString("\n") ;
				distance = GPS_getDistance(currentLong ,currentLat ,long_final ,lat_final) ;
				printf("%f",distance);
				if(distance >1000){
					RGB_clearOutput(0xE);
			RGB_setOutput (0x2);
			
		}else if ((distance<1000 && distance >200)){
			RGB_clearOutput(0xE);
			RGB_setOutput (0x2);
			RGB_setOutput (0x8);
		}else if (distance <200){
			RGB_clearOutput(0xE);
			RGB_setOutput (0x8);
			 
		}
		
		}
		
		
	}