#include "s3c2440.h"
#include "timer.h"
#include "interrupt.h"
#include "lib.h"
#include "task.h"


void timer_init(void)
{
	/*
	 PCLK 50M
	 Timer input clock Frequency = PCLK / {prescaler value+1} / {divider value}
	{prescaler value} = 0~255
	{divider value} = 2, 4, 8, 16

	 
	 对PCLK预分频，8位分频器   
	 [7:0]  Timer 0 and 1.
	 [15:8] Timer 2, 3 and 4. 
	*/
	//TCFG0 |= 0x3400;
	TCFG0 |= 0xff00; /* prescaler value prescaler value for Timer 2, 3 and 4    255*/

	/*二次分频 2，4，8，16*/
	//TCFG1 默认 1/2
	//TCFG1 |= (3 << 16);
	TCFG1 |= (1 << 16); // 4
	
	TCON &= (~(7 << 20));
	TCON |= (1 << 22);
	TCON |= (1 << 21);

	//TCNT4
	TCNTB4 = 65535;
	//TCNTB4 = 60000;
	TCON |= (1 << 20);
	TCON &= (~(1 << 21));

 	unmask_int(INT_TIMER4);
}


u32 sysTicks = 0;
void TIMER4_ISR(void)
{
	//info("timer4 isr");
	sysTicks++;

	if(current_task_over() == TRUE)
	{	
		//info("task schedule");
		task_schedule();
	}
}


