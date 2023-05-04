#include "SevenSegment.h"

void SevenSegment001_Set (unsigned char Value){
GPIO_PORTB_DATA_R=SevenSegmentArr[Value];
}

void SevenSegment010_Set (unsigned char Value){
GPIO_PORTA_DATA_R=SevenSegmentArr[Value];
}

void SevenSegment100_Set (unsigned char Value){
GPIO_PORTD_DATA_R=SevenSegmentArr[Value];
}
