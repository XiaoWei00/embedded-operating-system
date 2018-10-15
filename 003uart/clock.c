


#include "clock.h"
#include "s3c2440.h"



void sysclock_init(void)
{

	LOCKTIME = 0xFFFFFFFF;
	
	
	
	/*…Ë÷√FCLK°¢HCLK°¢PCLK*/
	CLKDIVN = (PDIVN ) | (HDIVN<<1) ;
	

	/*…Ë÷√MPLL*/
	MPLLCON = (SDIV)| (PDIV<<4) | (MDIV<<12) ;

}




