
#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "type.h"

#define _INTOFFSET(x) ( 1 << x)

#define EINT0 _INTOFFSET(0)
#define INT_IIMER4 _INTOFFSET(14) 



void interrupt_process(void);
void unmask_int(u32 offset);
void mask_int(u32 offset);
void clear_int(void);

void enable_irq(void);
void disable_irq(void);

#endif





