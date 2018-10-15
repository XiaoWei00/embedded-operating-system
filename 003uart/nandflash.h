





#ifndef _NANDFLASH_H_
#define _NANDFLASH_H_


/*

HCLK:100MHz


NFCONF:

TACLS  Duration = HCLK x TACLS

TWRPH0 Duration = HCLK x ( TWRPH0 + 1 )

TWRPH1 Duration = HCLK x ( TWRPH1 + 1 )
*/
#define TACLS   0
#define TWRPH0  1
#define TWRPH1  0

/*
NFCONT:

InitECC   1
MODE      1

*/

#define InitECC  1
#define MODE      1



#define nandflash_disenable()   NFCONT |= (1<<1)         /*第1位置1*/
#define nandflash_enable()   NFCONT &= ~(1<<1)       /*第1位清0*/ 



void nandflash_init(void);
void nandflash_read( unsigned int src, char *buff, unsigned int len);
void nandflash_write( char * buff,  unsigned int des,  unsigned int len);
void nandflash_erase( unsigned int des,  unsigned int len);
#endif








