







.text
.global _start

_start:

    /*…Ë÷√’ª£¨sp’ª÷∏’Î*/
	ldr sp, =4096 /*nand ∆Ù∂Ø*/
	bl main

halt:
	b halt







