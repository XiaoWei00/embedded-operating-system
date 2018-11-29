#ifndef _SYSTEMCALL_H_
#define _SYSTEMCALL_H_


#include "type.h"

u32 get_ticks(void);
void enable_irq(void);
void disable_irq(void);



#define SYSCALLNUM 4

#define SYSCALL(pnum,pdata,id,ret) 	do{ \
		asm volatile(					\
		"stmfd sp!, {%1}\n\t"			\
		"stmfd sp!, {%2}\n\t"			\
		"sub sp, sp, #4\n\t"			\
		"swi %3\n\t"					\
		"ldmfd sp!, {%0}\n\t"			\
		"add sp, sp, #8\n\t"			\
		:"=r"(ret)						\
		:"r"(pnum),"r"(pdata),"i"(id) 	\ 
		);}while(0)


#endif






