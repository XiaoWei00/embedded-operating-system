
/*
点亮LED
GPF4: 低电平点亮
GPFCON(0x56000050): 00 00 00 01 00 00 00 00    /0X0100
GPFDAT(0x56000054): 00000000                           / 0X00 
*/

.text
.global _start

_start:
	ldr r0, =0x56000050
	ldr r1, =0x0100
	str r1,[r0]
	ldr r0, =0x56000054
	ldr r1, =0x00
	str r1,[r0]

	/*死循环*/
halt:
	b halt



	
	
	