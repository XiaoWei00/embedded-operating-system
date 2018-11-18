



#include "uart.h"



int main(void)
{

	while(1)
	{
		uart_send_str("user program\r\n");
		delay();
	}
	return 0;
}


