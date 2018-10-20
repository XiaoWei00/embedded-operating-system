

#include "interrupt.h"
#include "s3c2440.h"
#include "lib.h"

/*XX中断禁止*/
void mask_int(u32 offset) 
{
	INTMSK &= ~(offset);
	INTMSK |= offset;
}
/*XX中断使能*/
void unmask_int(u32 offset)
{
	INTMSK &= ~(offset);   
}
/*清中断标志*/
void clear_int(void)
{
	u32 tmp = (1 << INTOFFSET);
	//printfk("intoffset=%d",tmp);
	SRCPND |= tmp;
	INTPND |= tmp;
}	
void interrupt_process(void)
{
	clear_int();

	enable_irq(); /*发生irq中断后，cpu禁止irq中断。使能irq中断，允许中断嵌套*/

	printfk("interrupt occured\r\n");

	//中断嵌套
	disable_irq(); /*在中断模式下，禁止再次发生中断*/
}

void enable_irq(void)
{	
  asm volatile(
	"mrs r4, cpsr\n\t"
	"bic r4, r4, #0x80\n\t"	/*bic 位清0*/
	"msr cpsr, r4\n\t"
	:::"r4"
	);
}	
void disable_irq(void)
{	
  asm volatile(
	"mrs r4, cpsr\n\t"
	"orr r4, r4, #0x80\n\t"  /*orr 位置1*/
	"msr cpsr, r4\n\t"
	:::"r4"
	);
}





