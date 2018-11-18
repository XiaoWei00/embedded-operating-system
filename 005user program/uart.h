
#ifndef _UART_H_
#define _URAT_H_

#include "s3c2440.h"




#define TX_OK  (UTRSTAT0 & (1<<2))
#define RX_OK  (UTRSTAT0 & 1 )




void uart_send_byte(const  char c);
void uart_send_str(const  char * str);
void delay(void);

#endif









