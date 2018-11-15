

#include "interrupt.h"
#include "s3c2440.h"
#include "lib.h"
#include "isr.h"


/*interrupt service routine*/
typedef void (*ISR)(void);

static ISR intServiceRoutine[32] = 
{
	NULL,//0
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,//10
	NULL,
	NULL,
	NULL,
	TIMER4_ISR,//14
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,//20
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	UART0_ISR, //28
	NULL
};	

static u32 intSource;
u32 subintSource;

void interrupt_process(void)
{

	intSource = get_int_source();
	subintSource = get_subint_source();
	
	clear_subint();
	clear_int();

	enable_irq(); /*发生irq中断后，cpu禁止irq中断。使能irq中断，允许中断嵌套*/
	
//	info("interrupt occured");

	/*判断中断源*/
	intServiceRoutine[intSource]();


	//中断嵌套	
	//disable_irq(); /*在中断模式下，禁止再次发生中断*/

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





