

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

	enable_irq(); /*����irq�жϺ�cpu��ֹirq�жϡ�ʹ��irq�жϣ������ж�Ƕ��*/
	
//	info("interrupt occured");

	/*�ж��ж�Դ*/
	intServiceRoutine[intSource]();


	//�ж�Ƕ��	
	//disable_irq(); /*���ж�ģʽ�£���ֹ�ٴη����ж�*/

}

void enable_irq(void)
{	
  asm volatile(
	"mrs r4, cpsr\n\t"
	"bic r4, r4, #0x80\n\t"	/*bic λ��0*/
	"msr cpsr, r4\n\t"
	:::"r4"
	);
}	
void disable_irq(void)
{	
  asm volatile(
	"mrs r4, cpsr\n\t"
	"orr r4, r4, #0x80\n\t"  /*orr λ��1*/
	"msr cpsr, r4\n\t"
	:::"r4"
	);
}





