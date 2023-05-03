#include "Main.h"

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
	
	
	while(~SW1){ SW1 = GPIO_PORTF_DATA_R&0x10;} //// Press SW1/PF4/ to store starting position
	GPS_read();
	GPS_format();
	startingLong=currentLong,startingLat=currentLat;
	//GPS_getDistance(startingLong ,startingLat , currentLong , currentLat);
	
  previousLong=startingLong, previousLat=startingLat;
	
////////////////////////////////////////////////////////////////////////// Program //////////////////////////////////////////////////////////////////////////
	while(~SW2){
	totalDistance+=	GPS_getDistance(previousLong , previousLat , currentLong , currentLat);    //Traveled distance
////////////////////////////////////////////////////////////////////////// Displaying Traveled Distance //////////////////////////////////////////////////////////////////////////
		
Split ( totalDistance);
SevenSegment001_Set (SevenSegmentArr[sig1]);    //PortB
SevenSegment010_Set (SevenSegmentArr[sig2]);    //PortA
SevenSegment100_Set (SevenSegmentArr[sig3]);    //PordD

////////////////////////////////////////////////////////////////////////// Leds //////////////////////////////////////////////////////////////////////////	
	distanceFromDestination=	GPS_getDistance(currentLong , currentLat , long_final,lat_final);   //Distance from final point
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
  GPS_read();                            ///Getting the new location
	GPS_format();	                         ///Formating the new location 
		
		
		
	SW2 = GPIO_PORTF_DATA_R&0x01; 	//// Press SW2/PF0/ to end the program
	}
	
	
	
}
