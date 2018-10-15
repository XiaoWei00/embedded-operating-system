


#ifndef _S3C2440_H_
#define _S3C2440_H_

#define _REG(X) (*((volatile unsigned int*)(X)))

/*WATCHDOG TIMER*/
#define WTCON _REG(0x53000000)

/****CLOCK****/
#define LOCKTIME _REG(0x4C000000)
#define MPLLCON _REG(0x4C000004)
#define CLKCON  _REG(0x4C00000C)
#define CLKSLOW _REG(0x4C000010)
#define CLKDIVN _REG(0x4C000014)


/***GPIO***/
#define GPFCON  _REG(0x56000050)
#define GPFDAT  _REG(0x56000054)




#endif








