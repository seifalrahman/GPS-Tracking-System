#ifndef SevenSegment
#define SevenSegment


#include "GPIO.h"
#include "tm4c123gh6pm.h"
#include "bit_utilities.h"

static unsigned char SevenSegmentArr[10]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10}; // common anode

void SevenSegment_Set (unsigned char Value);
void Split (double distance);
//void SevenSegment001_Set (unsigned char Value);
//void SevenSegment010_Set (unsigned char Value);
//void SevenSegment100_Set (unsigned char Value);
void display(int digit,char sig);
void Sys_tick_Init();
void SysTick_Handler();


#endif
