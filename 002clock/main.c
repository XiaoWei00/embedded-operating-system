




#include "s3c2440.h"
#include "clock.h"


/*
����LED
GPF4: �͵�ƽ����
GPFCON(0x56000050): 00 00 00 01 00 00 00 00    /0X0100
GPFDAT(0x56000054): 00000000                           / 0X00 
*/

int main()
{

	GPFCON = 0x0100;
	GPFDAT = 0;
	
 	return 0;
}



