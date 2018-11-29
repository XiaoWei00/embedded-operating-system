
#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "type.h"

#define _INTOFFSET(x) ( 1 << x)

/*INT*/
#define EINT0 _INTOFFSET(0)
#define INT_TIMER4 _INTOFFSET(14) 
#define INT_UART0 _INTOFFSET(28)


/*SUB INT*/
#define INT_RXD0  _INTOFFSET(0)
#define INT_TXD0  _INTOFFSET(1)


extern u32 subintSource;

void interrupt_process(void);
void enable_sysirq(void);
void disable_sysirq(void);


/*XX中断禁止*/
#define mask_int(offset) { \
	INTMSK &= ~(offset); \
	INTMSK |= (offset); }

/*XX中断使能*/
#define unmask_int(offset) INTMSK &= ~(offset)
/*清中断标志*/
#define  clear_int() { \
	u32 tmp = (1 << INTOFFSET); \
	SRCPND |= tmp; \
	INTPND |= tmp;}	

#define mask_subint(suboffset) { INTSUBMSK &= ~(suboffset); INTSUBMSK |= (suboffset); }

#define unmask_subint(suboffset) INTSUBMSK &= ~(suboffset)


#define clear_subint() SUBSRCPND |= SUBSRCPND

#define get_int_source() INTOFFSET

#define get_subint_source() SUBSRCPND

/*

Interrupt Mode:FIQ IRQ
Interrupt Pending Register:SRCPND INTPND
Interrupt Mask Register:INTMSK

*/

#endif





