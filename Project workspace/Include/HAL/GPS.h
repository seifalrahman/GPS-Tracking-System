#ifndef GPS_H
#define GPS_H


float GPS_getDistance(float currentLong , float currentLat , float destLong , float destLat);
void GPS_read2();
double GPStoDeg(double val);
float ToRad (float angle);

#endif