

#include "uart.h"
#include "s3c2440.h"


void uart_init(void)
{
	/*ʹ��UART_CLOCK*/

	//CLKCON = 
    /*Ĭ��ʹ��*/
	/****��������Ϊuart����***/
    /*�������������*/
	GPHCON &= ~((3<<4)|(3<<6)); 
	GPHCON |= ((2<<4) | (2<<6));
	
	/*GPH2,3��������*/
	GPHUP &= ~((1<<2)|(1<<3));


	/*ʹ��*/
	UCON0 |= (RX_EN) | (TX_EN<<2);
	//UCON0 = 0x00000005; /* PCLK,�ж�/��ѯģʽ */

	/*���ò�����*/
	UBRDIV0 = BAUB_RATE_9600;
 	
	/*��������λ����żУ��λ��ֹͣλ*/
	ULCON0 |= (WORD_LENGTH)|(STOP_BIT<<2)|(PARITY_MODE<<5);
	//ULCON0 = 0x00000003; /* 8n1: 8������λ, �޽���λ, 1��ֹͣλ */

	INTSUBMSK = ~(0x1);   	
	INTMSK = ~(0x1<<28);



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








