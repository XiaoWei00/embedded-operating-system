

#include "sdram.h"
#include "s3c2440.h"




void sdram_init(void)
{
     /*����Bank6 ����λ��   32λ*/
	// BWSCON |= (2<<24); //   0x   0 2(0010)   00, 00 00 
	   BWSCON  = (2<<24);
	 /*
	   ѡ����Ӵ洢������ SDARM
	   �е�ַ���е�ַ�����ʱ
	   �е�ַ�� 9
	 */
	 BANKCON6 &= ~(0xf);
	 BANKCON6 |= (1);  //

	/*SDRAMˢ�²���*/
	REFRESH = 0x8404F5;

	/*SDRAM BankSize*/
	//BANKSIZE |= (1<<7) | (1<<5) | (1<<4)| (1); // (10110001)
	BANKSIZE = (1<<7) | (1<<5) | (1<<4)| (1); // (10110001)


	MRSRB6 = 0x20;


		
}
















