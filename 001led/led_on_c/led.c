




/*
点亮LED
GPF4: 低电平点亮
GPFCON(0x56000050): 00 00 00 01 00 00 00 00    /0X0100
GPFDAT(0x56000054): 00000000                           / 0X00 
*/

int main()
{
	volatile unsigned int *GPFCON = (volatile unsigned int*)0x56000050;
	volatile unsigned int *GPFDAT = (volatile unsigned int*)0x56000054;

	*GPFCON = 0x0100;
	*GPFDAT = 0;
	
 	return 0;
}
