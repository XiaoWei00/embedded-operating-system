

#include "interrupt.h"
#include "s3c2440.h"
#include "lib.h"

void mask_int(u32 offset)
{
	INTMSK &= ~(offset);
	INTMSK |= offset;
}
void unmask_int(u32 offset)
{
	INTMSK &= ~(offset);   
}

void clear_int(void)
{
	u32 tmp = (1 << INTOFFSET);
	SRCPND |= tmp;
	INTPND |= tmp;
	
}	
void interrupt_process(void)
{
	
	printfk("interrupt occured\r\n");
	clear_int();
}

void enable_irq(void)
{	
  asm volatile(
	"mrs r4, cpsr\n\t"
	"bic r4, r4, #0x80\n\t"	/*bic Î»Çå0*/
	"msr cpsr, r4\n\t"
	:::"r4"
	);
}	
void disable_irq(void)
{	
  asm volatile(
	"mrs r4, cpsr\n\t"
	"orr r4, r4, #0x80\n\t"  /*orr Î»ÖÃ1*/
	"msr cpsr, r4\n\t"
	:::"r4"
	);
}





