#include "s3c2440.h"
#include "timer.h"
#include "interrupt.h"

void timer_init(void)
{

	/*
	 PCLK 50M
	 Timer input clock Frequency = PCLK / {prescaler value+1} / {divider value}
	 ��PCLKԤ��Ƶ��8λ��Ƶ��   
	 [7:0]  Timer 0 and 1.
	 [15:8] Timer 2, 3 and 4. 
	*/
	TCFG0 |= 0x3400; /**/

	/*���η�Ƶ 2��4��8��16*/
	//TCFG1 Ĭ�� 1/2
	TCFG1 |= (3 << 16);
	
	TCON &= (~(7 << 20));
	TCON |= (1 << 22);
	TCON |= (1 << 21);
	//TCNT4
	TCNTB4 = 60000;
	TCON |= (1 << 20);
	TCON &= (~(1 << 21));

 	unmask_int(INT_IIMER4);
}





