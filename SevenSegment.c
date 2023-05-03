#include "SevenSegment.h"

int sig1,sig2,sig3;
unsigned char SevenSegmentArr[10]={0x3F,0x6,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x6F};
	
void SevenSegment_Set (unsigned char Value){
GPIO_PORTB_DATA_R=SevenSegmentArr[Value];
}

void Split (double distance){
	int d=distance
	sig1=d%10;
	d/=10;
	sig2=d%10;
	d/=10;
	sig3=d%10;
}