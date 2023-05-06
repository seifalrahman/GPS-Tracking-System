#include "SevenSegment.h"

int sig1,sig2,sig3;
unsigned char SevenSegmentArr[10]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};     //common anode
unsigned char count=0;
void SevenSegment_Set (unsigned char Value){
GPIO_PORTB_DATA_R=SevenSegmentArr[Value];                 //(B0 --> a , B1--> b , ..........B6--> g)
}

void Split (double distance){      // call in main
	int d=distance
	sig1=d%10;
	d/=10;
	sig2=d%10;
	d/=10;
	sig3=d%10;
}

void display(int digit,char sig){
    GPIO_PORTB_DATA_R = 0x11;   // turn off leds (clear)
    GPIO_PORTA_DATA_R = digit;  // 1 enable LSB (A0)    2 enable second bit (A1)    4 enable MSB (A2)
    SevenSegment_Set(sig);
}

void Sys_tick_Init(){
    NVIC_ST_CTRL_R=0;
    NVIC_ST_RELOAD_R=80000-1;
    NVIC_ST_CURRENT_R=7;
    __enable_irq();
}

void SysTick_Handler(){
    if(count==0){           
        display(4,seg3);
        count++;
    }
    if(count==1){
        display(2,seg2);
        count++;
    }
    if(count==2){
        display(1,seg1);
        count++;
    }
}
