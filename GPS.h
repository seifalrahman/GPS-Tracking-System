#ifndef GPS1
#define GPS1
#include "tm4c123gh6pm.h"
#include "bit_utilities.h"
#include <string.h>
#include <stdlib.h>
#include <math.h> 
#include "UART.h"

#define PI 3.141592653589793238
static const double EARTH_RADIUS = 6371000 ;

static float currentLong, currentLat,speed ,finalLat=1052.563787;
static const double long_final,lat_final ;

void GPS_format();
void GPS_read();
float ToDegree (float angle);
float ToRad (float angle);
float GPS_getDistance(float currentLong , float currentLat , float destLong , float destLat);
void GPS_read();
void GPS_format();


#endif

