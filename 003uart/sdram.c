

#include "sdram.h"
#include "s3c2440.h"




void sdram_init(void)
{
     /*设置Bank6 数据位宽   32位*/
	// BWSCON |= (2<<24); //   0x   0 2(0010)   00, 00 00 
	   BWSCON  = (2<<24);
	 /*
	   选择外接存储器类型 SDARM
	   行地址与列地址间的延时
	   列地址数 9
	 */
	 BANKCON6 &= ~(0xf);
	 BANKCON6 |= (1);  //

	/*SDRAM刷新参数*/
	REFRESH = 0x8404F5;

	/*SDRAM BankSize*/
	//BANKSIZE |= (1<<7) | (1<<5) | (1<<4)| (1); // (10110001)
	BANKSIZE = (1<<7) | (1<<5) | (1<<4)| (1); // (10110001)


	MRSRB6 = 0x20;


		
}
















