







.text
.global _start

_start:

    /*����ջ��spջָ��*/
	ldr sp, =4096 /*nand ����*/
	bl main

halt:
	b halt







