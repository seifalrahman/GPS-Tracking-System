#ifndef SevenSegment
#define SevenSegment


#include "GPIO.h"
#include "tm4c123gh6pm.h"
#include "bit_utilities.h"

static unsigned char SevenSegmentArr[10]={0x3F,0x6,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x6F};

void SevenSegment001_Set (unsigned char Value);
void SevenSegment010_Set (unsigned char Value);
void SevenSegment100_Set (unsigned char Value);

#endif