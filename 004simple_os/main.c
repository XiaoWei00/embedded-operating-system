
#include "s3c2440.h"
#include "lib.h"
#include "clock.h"
#include "uart.h"
#include "sdram.h"
#include "nandflash.h"
#include "level1init.h"

typedef void (*init_func)(void);

static init_func init[]={
//	sysclock_init,
	uart_init,
//	sdram_init,
//	nandflash_init,
//	copy2sdram,
//	bss_init,
	NULL
};

void hardware_init(init_func init[])
{
	int i;
	for(i=0;init[i];i++)
	{
		init[i]();	
	}
}

void board_init(void)
{
   hardware_init(init);
}	

char c = 'a';
int main(void)
{
	
	board_init();
/*	
	char *p = "this is a string";
	int num = 255;
	int t = -1;
	
	printfk("simple os!\r\n");
	printfk("c=%c\r\n",c);
	printfk("%s\r\n",p);//%s
	printfk("%d\r\n",num);
	printfk("%u\r\n",num);
	printfk("%x\r\n",num);
	printfk("%o\r\n",num);

	printfk("%d\r\n",t);
	printfk("%u\r\n",t);
	printfk("%x\r\n",t);
	printfk("%o\r\n",t);
*/
	uart_send_str("simple os\r\n");
	GPFCON = 0x0100;	
	GPFDAT = 0;

	return 0;
	
}







