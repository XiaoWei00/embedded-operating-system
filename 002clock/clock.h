
#ifndef _CLOCK_H_
#define _CLOCK_H_

/* 12.0000MHz  400.00 MHz*/
#define MDIV 92
#define PDIV 1 
#define SDIV 1

/*
12.0000MHz  48.00 MHz
The 48.00MHz and 96MHz output is used for UPLLCON register.

#define MDIV 56
#define PDIV 2 
#define SDIV 2
*/
/*
FCLK: 400MHz
HCLK: 100MHz
PCLK: 50MHz
*/
#define PDIVN 1
#define HDIVN 2



/**MPLL**/
/*
Mpll = (2 * m * Fin) / (p * 2 S )
m = (MDIV + 8), p = (PDIV + 2), s = SDIV

MDIV 92
PDIV 1
SDIV 1

Input Frequency 12MHz  
Output Frequency 400.00 MHz 
*/


/*FCLK   HCLK  PCLK*/
/*
HDIVN  
00 : HCLK = FCLK/1.
01 : HCLK = FCLK/2.
10 : HCLK = FCLK/4 when CAMDIVN[9] = 0.
HCLK= FCLK/8 when CAMDIVN[9] = 1.


PDIVN
0: PCLK has the clock same as the HCLK/1.
1: PCLK has the clock same as the HCLK/2.
*/

void sysclock_init(void);

#endif















