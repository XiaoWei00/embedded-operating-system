

#include "uart.h"
#include "s3c2440.h"
#include "lib.h"
#include "interrupt.h"

/*UART0*/
void uart_init(void)
{
	
	/*使能UART_CLOCK*/
	/*默认使能*/
	 
	/*设置引脚为uart功能*/
    /*先清除，再设置*/
	GPHCON &= ~((3<<4)|(3<<6)); 
	GPHCON |= ((2<<4) | (2<<6));
	
	/*GPH2,3引脚上拉*/
	GPHUP &= ~((1<<2)|(1<<3));


	/*使能*/
	UCON0 |= (RX_EN) | (TX_EN<<2);
	//UCON0 = 0x00000005; /* PCLK,中断/查询模式 */
	
	/*设置波特率*/
	UBRDIV0 = BAUB_RATE_9600;

	/*设置数据位，奇偶校验位，停止位*/
	ULCON0 |= (WORD_LENGTH)|(STOP_BIT<<2)|(PARITY_MODE<<5);
	//ULCON0 = 0x00000003; /* 8n1: 8个数据位, 无较验位, 1个停止位 */

	unmask_subint(INT_RXD0);
	unmask_int(INT_UART0);
	
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


extern u32 exefileSize;
extern char *exefileBuff;
extern u8 exefileFlag;

static u8 startFlag = 0;
static char flag[2] = {0};

void UART0_ISR(void)
{
	
//	info("uart0 ISR");
	
	if((subintSource & INT_RXD0) != 0)
	{
	
		/*uart0 receive interrupt*/
		//	info("uart0 receive");

		/*receive exe file*/			
	 	flag[1] = flag[0];
		flag[0] = uart_read_byte();

	//	printfk("flag1=%c\r\n",flag[1]);
	//	printfk("flag0=%c\r\n",flag[0]);
			
		if(flag[0] == 'T' && flag[1] == 'S' && startFlag == 0)
		{
		/*exe file transmit statr*/
		startFlag = 1;
		}
		else if(flag[0] == 'D' && flag[1] == 'N' && startFlag == 1)
		{
			/*exe file transmit end*/
			startFlag = 0;
			exefileFlag = 1;
			/*ignore last N*/
			//exefileSize++;
	
		}
		else if(startFlag == 1)
		{
			exefileBuff[exefileSize++] = flag[0];
		}	
		
	}
	else if((subintSource & INT_TXD0) != 0)
	{
		/*uart0 send interrupt*/
	//	info("uart0 send");
	}	
		
	
}	

