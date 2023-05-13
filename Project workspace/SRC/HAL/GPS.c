#include "../../Include/MCAL/tm4c123gh6pm.h"
#include <string.h>
#include <stdint.h>
#include <math.h> 
#include <stdio.h>
#include <stdlib.h>
#define PI 3.141592653589793238 
#define GET_REG(reg)        (reg&0xff)

char GPS_logName[]="$GPRMC,";
char GPS[80] ;
char Valid [1];
char N_or_S [1];
char E_or_W [1];
float currentLong, currentLat,speed ;
double long_final=31.2806451,lat_final=30.0648936; 
char longi [20]={0} ;
char speedd [10]={0} ;
char lat [20]={0} ;

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
