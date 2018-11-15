
#include "s3c2440.h"
#include "lib.h"
#include "uart.h"
#include "timer.h"
#include "memory.h"
#include "storage.h"
#include "fs.h"

typedef void (*init_func)(void);

static init_func init[]={
	uart_init,
	timer_init,
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


//exefile
char *exefileBuff = NULL;
u32 exefileSize = 0;
u8 exefileFlag = 0;


char c = 'a';
int main(void)
{
	enable_irq();
	hardware_init(init);

	int i = 0;

	kmalloc_init();
	
	ramdisk_init();
		
	fs_init();
	
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
	/* receive executable file from uart to exefilebuff */
	exefileBuff = (char *)kmalloc(512);
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
				printfk("%c\r\n",rexefileBuff[i]);
			}
		
			kfree(rexefileBuff);
			
			exefileSize = 0;
			
		}


	}	
		
	kfree(exefileBuff);

	
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

	s8 *p2 = (s8 *)get_free_pages(6);
	printfk("p2 = %x\r\n",p2);

	s8 *p3 = get_free_pages(8);
	printfk("p3 = %x\r\n",p3);
	
	put_free_pages(p1,0);
	put_free_pages(p2,0);
	put_free_pages(p3,0);


	s8 *p4 = (s8 *)kmalloc(18);
	printfk("p4 = %x\r\n",p4);

	s8 *p5 = (s8 *)kmalloc(44);
	printfk("p5 = %x\r\n",p5);

	s8 *p6 = kmalloc(345);
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
	
		
		if(testbuffsize >= 4)
		{
			printfk("%s\r\n",testbuff);
			testbuffsize = 0;
		}	
	}
*/
	

	return 0;
	
}







