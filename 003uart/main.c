

#include "s3c2440.h"
#include "clock.h"
#include "uart.h"

void UART0_ISR(void);

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
	NULL,//14
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
void enable_irq(void)
{	
  asm volatile(
	"mrs r4, cpsr\n\t"
	"bic r4, r4, #0x80\n\t"	/*bic 位清0*/
	"msr cpsr, r4\n\t"
	:::"r4"
	);
}
#define  clear_int() { \
	unsigned int tmp = (1 << INTOFFSET); \
	SRCPND |= tmp; \
	INTPND |= tmp;}	

#define clear_subint() SUBSRCPND |= SUBSRCPND

#define get_int_source() INTOFFSET

#define get_subint_source() SUBSRCPND


unsigned int  intSource;
unsigned int  subintSource;
void interrupt_process(void)
{	

//	intSource = get_int_source();
//	subintSource = get_subint_source();

	clear_subint();
	clear_int();
	
	uart_send_str("int\r\n");
//	intServiceRoutine[intSource]();

}	

/*
点亮LED
GPF4: 低电平点亮
GPFCON(0x56000050): 00 00 00 01 00 00 00 00    /0X0100
GPFDAT(0x56000054): 00000000                           / 0X00 
*/
//char a;
int main()
{

	enable_irq();
	
	GPFCON = 0x0100;
	GPFDAT = 0;

  	
	uart_send_str("hello world!");
	//uart_send_byte(0xff);
	//uart_send_byte(a);

	while(1)
	{
	
		char c;
	  	c=uart_read_byte();
		uart_send_byte(c);
	
	}
	
 	return 0;
}

void UART0_ISR(void)
{	
	uart_send_str("uart0 ISR\r\n");
	if((subintSource & 0x1) != 0)
	{	
		uart_send_str("uart0 receive\r\n");
	}
	else if((subintSource & 0x2) != 0)
	{
		uart_send_str("uart0 send\r\n");
	}	

}	

