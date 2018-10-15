

#include "s3c2440.h"
#include "clock.h"
#include "uart.h"

/*
点亮LED
GPF4: 低电平点亮
GPFCON(0x56000050): 00 00 00 01 00 00 00 00    /0X0100
GPFDAT(0x56000054): 00000000                           / 0X00 
*/
//char a;
int main()
{

	GPFCON = 0x0100;
	GPFDAT = 0;

  	
	//uart_send_str("hello world!");
	uart_send_byte(0xff);
	//uart_send_byte(a);

	while(1)
	{
		char c;
	  	c=uart_read_byte();
		uart_send_byte(c);
	}
	
 	return 0;
}



