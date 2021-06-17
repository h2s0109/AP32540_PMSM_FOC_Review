
/* Templete for Debug_port*/
/* find P33, Pin3,PCL3,PS3,P3*/ 

#include "gpio.h"
/*Initialize Output pin*/
/*void Debug_port_Initialization(void)
{
	P00_IOCR8.B.PC10 = 0x10;
	P02_IOCR0.B.PC0	 = 0x10;
	P02_IOCR0.B.PC1  = 0x10;
	P02_IOCR0.B.PC2  = 0x10;
	P02_IOCR0.B.PC3  = 0x10;
	P20_IOCR4.B.PC6  = 0x10;
	P14_IOCR0.B.PC2  = 0x10;
	P14_IOCR8.B.PC8  = 0x10;
}*/

/*Initialize output pin*/
void Debug_port_Initialization(void)
{
	P02_IOCR0.B.PC3 = 0x10;
}

/*Set the output pin*/
void Port_P33_Pin3_set(void)
{
	P02_OMSR.B.PS3 = 0x1;
}

/*Clear the Output pin*/
void Port_P33_Pin3_clr(void)
{
	P02_OMCR.B.PCL3 = 0x1;
}

/*Inverse the Output pin*/
void Port_P33_Pin3_inv(void)
{
    if(P02_OUT.B.P3 == 0x1)
    {
        Port_P33_Pin3_clr();
    }
    else
    {
        Port_P33_Pin3_set();
    }
} 