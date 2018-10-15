

#include "sdram.h"
#include "s3c2440.h"


void sdram_init(void)
{
	/*设置Bank6 数据位宽  32位*/
	BWSCON = (2 << 24);

	/*
    1.设置外接存储器类型 :SDRAM
    2.行地址与列地址间延时
    3.列地址数:9 
	*/
	 BANKCON6 &= ~(0xf);	 
	 BANKCON6 |= (1);
	 
	/*设置SDRAM刷新参数*/
	REFRESH = 0x8404F5;
	
	/*设置SDRAM Banksize 大小*/
	BANKSIZE = (1<<7) | (1<<5) | (1<<4)| (1); // (10110001)
	MRSRB6 = 0x20;

}







