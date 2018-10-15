
#ifndef _UART_H_
#define _URAT_H_


#define UART0_CLK_EN 
/*
UART channel 0
RXD0/GPH3
TXD0/GPH2
*/
#define TX0  2
#define RX0  2 


/*
ULCON0 :
Parity Mode               0xx = No parity 
Number of Stop Bit    0 = One stop bit per frame  1 = Two stop bit per frame
Word Length          11 = 8-bits
*/
#define PARITY_MODE 0
#define STOP_BIT    0
#define WORD_LENGTH  3

/*
UCON0:  0x00
FCLK Divider 
Clock Selection      Select PCLK, UEXTCLK or FCLK/n for the UART baud rate.   00, 10 = PCLK
Tx Interrupt Type  0
Rx Interrupt Type  0
*/
#define TX_INT_TYPE 0
#define RX_INT_TYPE 0
#define TX_MODE  0
#define RX_EN 1
#define TX_EN 1


/*
UTRSTAT0   
BIT2  Transmitter empty   1 = Transmitter (transmit buffer & shifter register) empty

*/

#define TX_OK  (UTRSTAT0 & (1<<2))
#define RX_OK  (UTRSTAT0 & 1 )

/*
UBRDIVn = (int)( UART clock / ( buad rate x 16) ) ¨C1
UART clock : PCLK  50MHz
*/

#define BAUD_RATE 26  /*(115200)*/




void uart_init(void);
void uart_send_byte(const  char c);
void uart_send_str(const  char * str);
char uart_read_byte(void);


#endif









