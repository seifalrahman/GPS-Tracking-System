#include "../Include/MCAL/tm4c123gh6pm.h"
#include "../Include/MCAL/UART.h"
#include "../Include/MCAL/GPIO.h"
#include <string.h>
#include <stdint.h>
#include <math.h> 
#include <stdio.h>
#include <stdlib.h>
#define PI 3.141592653589793238 
#define GET_REG(reg)        (reg&0xff)




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
				prevlat=currentLat   ;
				prevlong=currentLong ;
				GPS_read2()          ;
				total_distance+=GPS_getDistance( currentLong ,  currentLat , prevlong , prevlat) ;
			 //RGB_clearOutput(0xE);
			 // RGB_setOutput (0x8);
		   
				//UART_outString("lat  is ") ;
			
				//UART_outString(lat);
				//UART_outString("\n") ;
			  //UART_outString("long  is ") ;
				//UART_outString(longi);
				//UART_outString("\n") ;
				distance = GPS_getDistance(currentLong ,currentLat ,long_final ,lat_final) ;
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

		total_distance=total_distance/2 ;
	
		
	}
