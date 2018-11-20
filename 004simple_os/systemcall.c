

#include "systemcall.h"
#include "timer.h"
#include "lib.h"
#include "interrupt.h"

typedef u32 (*syscall) (u32, u32);

static syscall sysFun[2] =
{
	sys_get_ticks,
	NULL
};

u32 system_call(u32 id,u32 pnum,u32 pdata,u32 sid)
{
	/*
	info("system call");
	printfk("56id=%x\r\n",id);
	printfk("pnum=%d\r\n",pnum);
	printfk("pdata=%x\r\n",pdata);
	printfk("60id=%x\r\n",sid);
	*/
	enable_irq();
	
	id = id & ~0xff000000;	
	if(sysFun[id] != NULL)
	{
		return sysFun[id](pnum,pdata);
	}		
	return 0;
}



u32 get_ticks(char *str)
{
	u32 ret = 0;
	SYSCALL(1,str,0,ret);
	return ret;
}


u32 sys_get_ticks(u32 pnum,u32 pdata)
{	
		printfk((char *)pdata);
		return sysTicks;
}		


/*
void stack_print(u32 syssp,u32 svcsp)
{
	u32 *sysp = (u32 *)syssp;
	u32 *svcp = (u32 *)svcsp;
	
	u32 i = 0;
	for(i = 0; i <= 18; i++)
	{
		printfk("syssp=%x\r\n",*(sysp + i));
	}
	for(i = 1; i <= 3; i++)
	{
		printfk("svcsp=%x\r\n",*(svcp - i));
	}	
}	
*/
