#include "GPS.h"

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
 
char * token ;
void GPS_read(){
	char recievedChar ; 
	char i=0 ;
	do{
		while(UART_GetChar()!=GPS_logName[i]);
		i++;
		}
	while(i!=6);
	//here i make sure that i recieved the correct log 
		strcpy(GPS,"");
		do {
			char fillGPScounter =0 ; 
			recievedChar=UART_GetChar();
			GPS[fillGPScounter++]=recievedChar ;
		}
		while(recievedChar!='*');	
}

const double long_final,lat_final ;
void GPS_format(){
	char noOfTokenStrings = 0 ;
	token = strtok (GPS, ",");
	do {
		strcpy(GPS_formated[noOfTokenStrings],token);
		token=strtok(NULL,",");
		noOfTokenStrings++;
	}
	while(token!=NULL);
	
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