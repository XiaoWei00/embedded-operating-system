

#include "uart.h"
#include "s3c2440.h"


void uart_send_byte(const char c)
{
	while(!(TX_OK));
	UTXH0 = c;
	
}

void uart_send_str(const char *str)
{
     if(str == NULL)
	 	return;

	while(*str != '\0')
	{
	
		uart_send_byte(*str++);

	}	

}


void delay(void)
{
	int i = 0,j = 0;
	for(i = 0;i < 4000;i++)
		for(j = 0 ; j < 100;j++);
}






