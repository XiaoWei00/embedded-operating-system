

#include "interrupt.h"
#include "s3c2440.h"
#include "lib.h"

/*XX�жϽ�ֹ*/
void mask_int(u32 offset) 
{
	INTMSK &= ~(offset);
	INTMSK |= offset;
}
/*XX�ж�ʹ��*/
void unmask_int(u32 offset)
{
	INTMSK &= ~(offset);   
}
/*���жϱ�־*/
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

	enable_irq(); /*����irq�жϺ�cpu��ֹirq�жϡ�ʹ��irq�жϣ������ж�Ƕ��*/

	printfk("interrupt occured\r\n");

	//�ж�Ƕ��
	disable_irq(); /*���ж�ģʽ�£���ֹ�ٴη����ж�*/
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





