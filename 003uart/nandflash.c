

#include "nandflash.h"
#include "s3c2440.h"
#include "uart.h"

static void nandflash_addr(char addr);
static void nandflash_cmd(char cmd);
static void nandflash_write_data(char data);
static char nandflash_read_data(void);
static int IsNandflashRunning(void);
static void wait(void);

static void wait(void)
{
    while (!(NFSTAT & 1));
}

void nandflash_init(void)
{
	NFCONF = (TACLS<<12) | (TWRPH0<<8) | (TWRPH1<<4);
	
	NFCONT = (InitECC<<4) | (MODE<<0) | (1<<1);

	if(!IsNandflashRunning())
	{
		//uart_send_str("nand flash init error!");
	}
	else
	{
		//uart_send_str("nand flash init ok!");
	}	
	
}
static void nandflash_write_data(char data)
{
	 NFDATA = data;
}
static char nandflash_read_data(void)
{
	return NFDATA;
}
static void nandflash_addr(char addr)
{
	 volatile int i;
	 NFADDR = addr;
	 for(i=0; i<10; i++);
}

static void nandflash_cmd(char cmd)
{	
	volatile int i;
	NFCMMD = cmd;
	for(i=0; i<10; i++);
}

void nandflash_read(unsigned int src, char *buff,unsigned int len)
{
	/*len src 页对齐?*/
	
	unsigned int row =  (src / 2048);		/*行地址*/
	unsigned int col =  (src % 2048);		/*列地址*/
	int i = 0;
/*
	uart_send_byte((char)(len & 0xff));
	uart_send_byte((char)((len>>8) & 0xff));
    uart_send_byte((char)((len>>16) & 0xff));
	uart_send_byte((char)((len>>24) & 0xff));
*/

	nandflash_enable();

	while(i < len )
  	{
  		
		nandflash_cmd(0x00);

		nandflash_addr((char)(col & 0xff));
		nandflash_addr((char)((col>>8) & 0xff));

		nandflash_addr((char)(row & 0xff));
		nandflash_addr((char)((row>>8) & 0xff));
		nandflash_addr((char)((row>>16) & 0xff));

		nandflash_cmd(0x30);

		wait();
      
		for(;(col < 2048) && (i < len);col++)
		{
			buff[i++] = nandflash_read_data();
			//uart_send_byte(buff[i]);
		}

		if(i == len)
			break;

		col = 0;
		row++;
		
	}
	
	nandflash_disenable();
	
}	

void nandflash_write( char *buff,  unsigned int des,  unsigned int len)
{

}
void nandflash_erase( unsigned int des,  unsigned int len)
{

}

static int IsNandflashRunning(void)
{
		/*片选*/
		nandflash_enable();

		nandflash_cmd(0x90);

		nandflash_addr(0x00);

		char buff[5] = {0};
		int i = 0; 
		for(i = 0;i < 5; i++)
		{
			buff[i] =  nandflash_read_data();

		}
		nandflash_disenable();

		/*
		for(i = 0;i < 5; i++)
		{
			uart_send_byte(buff[i]);

		}
		*/
		if((buff[0] == 0xEC) && (buff[1] == 0xDA) && (buff[2] == 0x10) && (buff[3] == 0x95) && (buff[4] == 0x44))
		{
			return 1;
		}

		return 0;	

}




