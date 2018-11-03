
#include "s3c2440.h"
#include "lib.h"
#include "uart.h"
#include "timer.h"
#include "memory.h"

typedef void (*init_func)(void);

static init_func init[]={
	uart_init,
	//timer_init,
	page_map_init,
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

void delay(void)
{
	int i = 0,j = 0;
	for(i = 0;i < 4000;i++)
		for(j = 0 ; j < 100;j++);
}	

char c = 'a';
int main(void)
{
	enable_irq();
	hardware_init(init);
	
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
	
	s8 *p1 = (s8 *)get_free_pages(0);
	printfk("p1 = %x\r\n",p1);

	s8 *p2 = (s8 *)get_free_pages(6);
	printfk("p2 = %x\r\n",p2);

	s8 *p3 = get_free_pages(8);
	printfk("p3 = %x\r\n",p3);
	
	put_free_pages(p1,0);
	put_free_pages(p2,0);
	put_free_pages(p3,0);
	
	GPFCON = 0x0100;	
	GPFDAT = 0;
	/*	
	while(1)
	{
		printfk("wait\r\n");
		delay();
	}
	*/
	return 0;
	
}







