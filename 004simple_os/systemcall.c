

#include "systemcall.h"
#include "timer.h"
#include "lib.h"
#include "interrupt.h"
#include "uart.h"

typedef u32 (*syscall) (u32, u32);



u32 sys_get_ticks(u32 pnum, u32 pdata);
u32 sys_enable_irq(u32 pnum, u32 pdata);
u32 sys_disable_irq(u32 pnum, u32 pdata);

static u32 usrIrqFlag = 0; //disable

static syscall sysFun[SYSCALLNUM] =
{
	sys_get_ticks,
	sys_enable_irq,
	sys_disable_irq,
	NULL
};

u32 system_call(u32 id,u32 pnum,u32 pdata)
{

	enable_sysirq();
	
	id = id & ~0xff000000;	
	if(sysFun[id] != NULL)
	{
		return sysFun[id](pnum,pdata);
	}
	
	return 0;
}



u32 get_ticks(void)
{
	u32 ret = 0;
	SYSCALL(0,0,0,ret);
	return ret;
}
u32 sys_get_ticks(u32 pnum,u32 pdata)
{	
		return sysTicks;
}

void enable_irq(void)
{	
	u32 ret = 0;
	SYSCALL(0,0,1,ret);
}

u32 sys_enable_irq(u32 pnum,u32 pdata)
{
	usrIrqFlag = 1; //enable
	return usrIrqFlag;
}	

void disable_irq(void)
{
	u32 ret = 0;
	SYSCALL(0,0,2,ret);
}	

u32 sys_disable_irq(u32 pnum, u32 pdata)
{
	usrIrqFlag = 0;
	return usrIrqFlag;
}	

u32 usr_irq(u32 spsr)
{
	if(usrIrqFlag == 1) // enable irq in usr mode
	{
		// clear 8-bit
		spsr &= ~0x80;
	}
	else  //disable irq in usr mode
	{
		//set 8-bit
		spsr |= 0x80;
	}	
		
	return spsr;	
}	

