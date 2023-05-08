//#include "Main.h"
#include "TM4C123.h"
#include "bit_utilities.h"
#include <string.h>
#include <stdlib.h>
#include <math.h> 
#define GPIO_SW1 0
#define GPIO_SW2 1
#define GPIO_SW_NOT_PRESSED 1

///PortF LED color
#define GPIO_RED_LED 0
#define GPIO_GREEN_LED 1
#define GPIO_BLUE_LED 2

///PortF LED state ON/OFF
#define GPIO_LED_OFF 0
#define GPIO_LED_ON 1


//#include "SevenSegment.h"
//#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
//#include "TM4C123.h"
//************************sevensegment.c*******************************
int sig1,sig2,sig3;
unsigned char SevenSegmentArr[10]={0x3F,0x6,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x6F};
	
void SevenSegment_Set (unsigned char Value){
 GPIO_PORTB_DATA_R =SevenSegmentArr[Value];
}
void SevenSegment001_Set (unsigned char Value){
GPIO_PORTB_DATA_R=SevenSegmentArr[Value];
}
void SevenSegment010_Set (unsigned char Value){
GPIO_PORTA_DATA_R=SevenSegmentArr[Value];
}

void SevenSegment100_Set (unsigned char Value){
GPIO_PORTD_DATA_R=SevenSegmentArr[Value];
}
void Split (double distance){
	int d=distance ;
	sig1=d%10;
	d/=10;
	sig2=d%10;
	d/=10;
	sig3=d%10;
}

//************************************************************************************************
//********************************UART.c*****************************************************
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
 //*****************************************************
 //***********************LED.c**********************
 void LED_Setup(){
	SYSCTL_RCGCGPIO_R |= 0x20;
	while(!(SYSCTL_PRGPIO_R & 0x20));
	GPIO_PORTF_LOCK_R= 0x4C4F434B;
	GPIO_PORTF_CR_R= 0xFF;
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
//***********************************************************
//*******************************GPS.c*********************
const double EARTH_RADIUS = 6371000 ;
#define PI 3.141592653589793238 
float ToDegree (float angle ){
		int degree = (int)angle/100 ; 
	  float minutes = angle -(float)degree*100;
		return (degree+(minutes/60)) ;
}
float ToRad (float angle){
		return angle *PI/100 ;
}
 float GPS_getDistance(float currentLong , float currentLat , float destLong , float destLat){
		//Get Radian 
	 float currentLongRad=ToRad((currentLong)) ;
	 float currentLatRad=ToRad((currentLat)) ;
	 float destLongRad = ToRad((destLong)) ;
	 float destLatRad=ToRad((destLat)) ;
	 //Get Difference 
	 float longDiff = destLongRad- currentLongRad ;
	 float latDiff = destLatRad - currentLatRad ;
	 // calculate Distance 
	 float a = pow (sin(latDiff/2),2) +cos(currentLatRad)*cos(destLatRad)*pow(sin(longDiff/2),2) ; 
		double c = 2*atan2(sqrt(a) , sqrt(1-a) ) ;
	 return 6371000*c ;

 }
char GPS_logName[]="$GPRMC,";
char GPS[80] ;
char GPS_formated[12][20] ;
char * token ;
void GPS_read(){
	char recievedChar ; 
	char i=0 ;
	do{
		while(UART_GetChar()!=GPS_logName[i]);
		i++;
		}while(i!=6);
	//here i make sure that i recieved the correct log 
		strcpy(GPS,"");
		do {
			char fillGPScounter =0 ; 
			recievedChar=UART_GetChar();
			GPS[fillGPScounter++]=recievedChar ;
		}while(recievedChar!='*');
	
}
float currentLong, currentLat,speed ,finalLat=1052.563787;
const double long_final,lat_final ;
void GPS_format(){
	char noOfTokenStrings = 0 ;
	token = strtok (GPS, ",");
	do {
		strcpy(GPS_formated[noOfTokenStrings],token);
		token=strtok(NULL,",");
		noOfTokenStrings++;
	}while(token!=NULL);
	
				if(strcmp(GPS_formated[1],"A")==0){//to check that it is valid 
					if(strcmp(GPS_formated[3],"N")==0)
						currentLat=atof(GPS_formated[2]);
					else
						currentLat=-atof(GPS_formated[2]) ;
					if(strcmp(GPS_formated[5],"E")==0)
						currentLong=atof(GPS_formated[4]);
					else
						currentLong=-atof(GPS_formated[4]);
						
				}
	
	
	
}

 
//**************************************************************
//****************************GPIO.c***************************

void GPIOB_Init () {
  SET_BIT(SYSCTL_RCGCGPIO_R,1);
  while(GET_BIT(SYSCTL_PRGPIO_R,1)==0);   
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
GPIO_PORTF_PDR_R = 0x11; // pull-down on PF0 and PF4 ************
GPIO_PORTF_DEN_R = 0x1F; // digital I/O on PF4-0
	
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
//*********************************************************



int main(void){
	
////////////////////////////////////////////////////////////////////////// Starting //////////////////////////////////////////////////////////////////////////
	int SW1=0,SW2=0;
	float startingLong,startingLat;
	float totalDistance=0, distanceFromDestination;
	float previousLong, previousLat;
	GPIOF_Init();
	GPIOB_Init ();
	GPIOA_Init ();
  GPIOD_Init ();
	LED_Setup();
	
	
	while(~SW1){ SW1 = GPIO_PORTF_DATA_R&0x10;} //// Press SW1/PF4/ to store the starting position
	GPS_read();
	GPS_format();
	startingLong=currentLong,startingLat=currentLat;
	//GPS_getDistance(startingLong ,startingLat , currentLong , currentLat);
	
  previousLong=startingLong, previousLat=startingLat;
	
////////////////////////////////////////////////////////////////////////// Program //////////////////////////////////////////////////////////////////////////
	while(~SW2){
	totalDistance+=	GPS_getDistance(previousLong , previousLat , currentLong , currentLat);    //The traveled distance
////////////////////////////////////////////////////////////////////////// Displaying Traveled Distance //////////////////////////////////////////////////////////////////////////
		
Split ( totalDistance);
SevenSegment001_Set (SevenSegmentArr[sig1]);    //PortB
SevenSegment010_Set (SevenSegmentArr[sig2]);    //PortA
SevenSegment100_Set (SevenSegmentArr[sig3]);    //PordD

////////////////////////////////////////////////////////////////////////// Leds //////////////////////////////////////////////////////////////////////////	
	distanceFromDestination=	GPS_getDistance(currentLong , currentLat , long_final,lat_final);   //Distance from current point to the final point
	previousLong =	currentLong;
	previousLat	= currentLat;
	LED_Start(distanceFromDestination);
/*  if(distanceFromDestination<=0.5){
		LED_Start(distanceFromDestination);
	}
	else{
	LED_Start(totalDistance);
	}
*/	
  	GPS_read();  	                          ///Reading the new location
	GPS_format();	                         ///Formating the new location 
		
	SW2 = GPIO_PORTF_DATA_R&0x01; 	//// Press SW2/PF0/ to end the program
	}
	
	
	
}
