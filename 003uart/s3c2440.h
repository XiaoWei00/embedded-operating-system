
#ifndef _S3C2440_H_
#define _S3C2440_H_

/*
Ĭ������ΪС��ģʽ
*/
#define NULL 0
#define _REG(X) (*((volatile unsigned int*)(X)))
#define _REG_BYTE(X) (*((volatile unsigned char*)(X)))

/*WATCHDOG TIMER*/
#define WTCON _REG(0x53000000)

/****CLOCK****/
#define LOCKTIME _REG(0x4C000000)
#define MPLLCON _REG(0x4C000004)
#define UPLLCON  _REG(0x4C000008)   
#define CLKCON  _REG(0x4C00000C)
#define CLKSLOW _REG(0x4C000010)
#define CLKDIVN _REG(0x4C000014)


/***GPIO***/
#define GPFCON  _REG(0x56000050)
#define GPFDAT  _REG(0x56000054)

#define GPHCON  _REG(0x56000070) 
#define GPHDAT  _REG(0x56000074) 
#define GPHUP   _REG(0x56000078)

/*****UART*****/
/*UART0 
RXD0/GPH3
TXD0/GPH2   
*/
#define ULCON0 _REG(0x50000000)
#define UCON0  _REG(0x50000004)
#define UFCON0 _REG(0x50000008)
#define UMCON0 _REG(0x5000000C)
#define UTRSTAT0 _REG(0x50000010)
#define UTXH0 _REG_BYTE(0x50000020) /*L*/
#define URXH0 _REG_BYTE(0x50000024) /*L*/
#define UBRDIV0 _REG(0x50000028)
/*SDRAM*/
#define BWSCON _REG(0x48000000)
#define BANKCON6 _REG(0x4800001C)
#define BANKCON7 _REG(0x48000020)

#define REFRESH _REG(0x48000024)
#define BANKSIZE _REG(0x48000028)
#define MRSRB6 _REG(0x4800002C)
#define MRSRB7 _REG(0x48000030)

/*NAND FLASH*/
#define NFCONF _REG(0x4E000000)
#define NFCONT _REG(0x4E000004)

#define NFCMMD _REG_BYTE(0x4E000008)
#define NFADDR _REG_BYTE(0x4E00000C)
#define NFDATA _REG_BYTE(0x4E000010)

#define NFSTAT _REG_BYTE(0x4E000020)

#endif







