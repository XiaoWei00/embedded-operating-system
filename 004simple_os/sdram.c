

#include "sdram.h"
#include "s3c2440.h"


void sdram_init(void)
{
	/*����Bank6 ����λ��  32λ*/
	BWSCON = (2 << 24);

	/*
    1.������Ӵ洢������ :SDRAM
    2.�е�ַ���е�ַ����ʱ
    3.�е�ַ��:9 
	*/
	 BANKCON6 &= ~(0xf);	 
	 BANKCON6 |= (1);
	 
	/*����SDRAMˢ�²���*/
	REFRESH = 0x8404F5;
	
	/*����SDRAM Banksize ��С*/
	BANKSIZE = (1<<7) | (1<<5) | (1<<4)| (1); // (10110001)
	MRSRB6 = 0x20;

}







