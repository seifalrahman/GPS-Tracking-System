#ifndef Bit_Utilies
#define Bit_Utilies

#define GET_BIT(reg1,bit)   ((reg1>>bit)&1)
#define GET_REG(reg)        (reg&0xff)

#define SET(reg,val)        reg |= val //set register value
#define SET_BIT(reg,val)    reg |= (1<<val) //set bit value

#define CLR(reg,val)        reg &=~val //clear register value
#define CLR_BIT(reg,val)    reg &=~(1<<val) //clear bit value

#endif
