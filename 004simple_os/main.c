
#include "s3c2440.h"
#include "lib.h"
#include "uart.h"
#include "timer.h"
#include "memory.h"
#include "storage.h"
#include "fs.h"
#include "task.h"

typedef void (*init_func)(void);

static init_func init[]={
	uart_init,
	timer_init,
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

// output
// input
// clobbered registers
void exec(u32 exeaddr)
{
	asm volatile(
	"mov pc, r0\n\t"    /*code*/  			
	);
}

int test_task(void *p)
{
	while(1)
	{
		printfk("test task %d\r\n",(u32)p);
		delay();
	}	
}	


//exefile
char *exefileBuff = NULL;
u32 exefileSize = 0;
u8 exefileFlag = 0;


char c = 'a';
int main(void)
{
	
	hardware_init(init);

/*
	
	u32 cpsr = get_cpsr();
	uart_send_byte((char)(cpsr)); // 1 D0

	
	enable_irq();
	
	cpsr = get_cpsr();
	uart_send_byte((char)(cpsr));  //8 

//	disable_irq();
*/
	


	int i = 0;

	page_map_init();
	
	kmalloc_init();

	ramdisk_init();
		
	fs_init();

	enable_irq();
	
	
	//test usr mode and sys mode 
/*	
	u32 cpsr = get_cpsr();
	uart_send_byte((char)(cpsr));
	
	enable_irq();

	cpsr = get_cpsr();
	uart_send_byte((char)(cpsr));

	disable_irq();

	cpsr = get_cpsr();
	uart_send_byte((char)(cpsr));

*/
	/*device driver*/
/*
	s8 buff[10] = {'0','1','2','3','4','5','6','7','8','9'};
	
	storage_device[RAMDISK]->dout(storage_device[RAMDISK],0,buff,sizeof(buff));

	for(i = 0; i < sizeof(buff); i++)
	{
		printfk("%c\r\n",buff[i]);
		printfk("%c\r\n",*((char *)(storage_device[RAMDISK]->start_pos + i)));
	}

*/


	/*file system*/
/*	
	char testbuff[32] = {0};
	fileSys[ROMFS]->fsStorage->dout(fileSys[ROMFS]->fsStorage,0,testbuff,sizeof(testbuff));

	for(i = 0; i < 8; i++)
	{
		printfk("%c\r\n",testbuff[i]);//romfs ±êÖ¾
	}
	
		u32 size = *((u32 *)(testbuff + 8));
		
		printfk("size=%d\r\n",size);
		printfk("size=%x\r\n",size);

		printfk("b2s(size)=%x\r\n",b2s_32_endian(size));//size
				
		printfk("cs=%x\r\n",*((u32 *)(testbuff + 12)));
		
		printfk("name=%s\r\n",testbuff + 16);

*/
		

	/*write file from buff to file system*/
/*	char wfilebuff[] = "0123456789";
	fileSys[ROMFS]->fs_write_file(wfilebuff,sizeof(wfilebuff),"root/number");
*/

	/*Read files from file system to  buff*/
/*	char rfilebuff[20] = {0};
	fileSys[ROMFS]->fs_read_file(rfilebuff,"root/number");
/*
	printfk("number.txt:\r\n");
	for(i = 0; i < sizeof(rfilebuff); i++)
	{
		printfk("%c\r\n",rfilebuff[i]);
	}
*/


	GPFCON = 0x0100;
	GPFDAT = 0;

	/*process / task*/
	
	task_init();
	
	do_fork(test_task,(void *)1);
	do_fork(test_task,(void *)2);

	while(1)
	{
		//printfk("this is kernel task\r\n");
		u32 ticks = get_ticks();	
		printfk("ticks=%d\r\n",sysTicks);
		delay();
	}	


	/*system call*/
/*
	while(1)
	{	
		u32 ticks = get_ticks();
		printfk("ticks=%d\r\n",sysTicks);
		delay();
	}	
*/

	/* receive executable file from uart to exefilebuff */
/*	exefileBuff = (char *)kmalloc(512);
	memset(exefileBuff, 0, 512);

	while(1)
	{

		if(exefileFlag)
		{	
			info("exefile");
			
			exefileFlag = 0;
		
			fileSys[ROMFS]->fs_write_file(exefileBuff,exefileSize,"root/test");

			char *rexefileBuff = (char *)kmalloc(exefileSize);
			
			fileSys[ROMFS]->fs_read_file(rexefileBuff,"root/test");

				
			printfk("test\r\n");
			for(i = 0; i < (exefileSize - 1); i++)
			{
				printfk("%c",rexefileBuff[i]);
			}
		
			kfree(rexefileBuff);
			
			exefileSize = 0;
			
		}


	}	
		
	kfree(exefileBuff);
*/

	/*execute user program*/
/*	exefileBuff = (char *)get_free_pages(5);
	if(exefileBuff == NULL)
	{
		info("malloc exefileBuff is error");
		return 0;
	}	
	//memset(exefileBuff,0,40960);
	while(1)
	{
		if(exefileFlag == 1)
		{
			info("receive exe file");

			exefileFlag = 0;
			
			fileSys[ROMFS]->fs_write_file(exefileBuff,exefileSize,"root/exe");
	
			char *rfileBuff = (char *)get_free_pages(5);
			if(rfileBuff == NULL)
			{
				info("malloc rfileBuff is error");
				return 0;
			}
			
			fileSys[ROMFS]->fs_read_file(rfileBuff,"root/exe");

			
			exefileSize = 0;
	        /*user space starts at 0x30100000*/	
/*		  	u32 exeAddr = elf_get_exeaddr(rfileBuff);

			put_free_pages(rfileBuff,5);

			put_free_pages(exefileBuff,5);
			
			exec(exeAddr);
		}	
				
	}

*/	

	/*printfk*/
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


    /*memory manage*/
/*

	s8 *p1 = (s8 *)get_free_pages(0);
	printfk("p1 = %x\r\n",p1);

	s8 *p2 = (s8 *)get_free_pages(4);
	printfk("p2 = %x\r\n",p2);

	s8 *p3 = (char *)get_free_pages(3);
	printfk("p3 = %x\r\n",p3);
	
	put_free_pages(p1,0);
	put_free_pages(p2,4);
	put_free_pages(p3,3);

	

	p1 = (s8 *)get_free_pages(0);
	printfk("p1 = %x\r\n",p1);

	p2 = (s8 *)get_free_pages(2);
	printfk("p2 = %x\r\n",p2);

	p3 = (char *)get_free_pages(1);
	printfk("p3 = %x\r\n",p3);
	
	put_free_pages(p1,0);
	put_free_pages(p2,2);
	put_free_pages(p3,1);


	s8 *p4 = (s8 *)kmalloc(18);
	printfk("p4 = %x\r\n",p4);

	s8 *p5 = (s8 *)kmalloc(44);
	printfk("p5 = %x\r\n",p5);

	s8 *p6 = (s8 *)kmalloc(345);
	printfk("p6 = %x\r\n",p6);
	
	kfree(p4);
	kfree(p5);
	kfree(p6);
*/	

/*	
	while(1)
	{
		
		char tmp = uart_read_byte();
		uart_send_byte(tmp);
	}
*/
	return 0;
	
}







