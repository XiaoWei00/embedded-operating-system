

#include "uart.h"
#include "s3c2440.h"
#include "lib.h"

void uart_init(void)
{
	/****使能UART_CLOCK*/

	//CLKCON 
    /*默认使能*/
	/****设置引脚为uart功能***/
    /*先清除，再设置*/
	GPHCON &= ~((3<<4)|(3<<6)); 
	//GPHCON |= (TX0<<4)|(RX0<<6);
	GPHCON |= ((2<<4) | (2<<6));
	/*GPH2,3引脚上拉*/
	GPHUP &= ~((1<<2)|(1<<3));


	/****使能*******/

	UCON0 |= (RX_EN) | (TX_EN<<2);
	//UCON0 = 0x00000005; /* PCLK,中断/查询模式 */
	/****设置波特率115200*****/
	UBRDIV0 = BAUD_RATE;
 	
	/****设置数据位，奇偶校验位，停止位****/

	ULCON0 |= (WORD_LENGTH)|(STOP_BIT<<2)|(PARITY_MODE<<5);
	//ULCON0 = 0x00000003; /* 8n1: 8个数据位, 无较验位, 1个停止位 */
	
	out_str = uart_send_str;


}


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

char uart_read_byte(void)
{
      while(!(RX_OK));
	  return URXH0; 
}



