#include "level1init.h"
#include "nandflash.h"
#include "lib.h"

static boot_from_norflash(void)
{
	/*判断nand flash启动 还是nor flash启动*/
	volatile int *p = (volatile int *)0;

	int saveVal = *p;
	
	*p = 0x12345678;

	/*写成功，nand flash启动*/
	if(*p == 0x12345678)
	{
		*p = saveVal;
		return 0;
	}
	else /*nor flash启动*/
	{
		return 1;
	}	


}

void copy2sdram(void)
{

	extern int code_start,bss_start;

	volatile unsigned int *src = (volatile unsigned int *)0;
    volatile unsigned int *des = (volatile unsigned int *)&code_start;
	volatile unsigned int *end = (volatile unsigned int *)&bss_start;

	unsigned int len = (end - des) * sizeof(int);


	if(boot_from_norflash())
	{
		while(des < end)	
			*des++ = *src++;
	}
	else
	{
		nandflash_read(0, (char *)des,len);
	}		
}

void bss_init(void)
{
	extern int bss_start,bss_end;
	volatile unsigned int *src = (volatile unsigned int *)&bss_start;
	volatile unsigned int *end = (volatile unsigned int *)&bss_end;

	while(src <= end)
	{
		*src++ = 0; 
	}
}




