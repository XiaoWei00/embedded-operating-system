





.text
.global _start

_start:

	/*�ؿ��Ź�*/
	ldr r0, =0x53000000   /*WTCON*/
	ldr r1, =0
	str r1, [r0]

    /*����ջ��spջָ��*/
	/*�ж�nor flash���� ����nand flash����*/
	/*��0��ַдֵ����дΪnand����������дΪnor����*/
	ldr r1, =0
	ldr r0, [r1]    /*����0��ַ��ֵ��r0*/
	str r1, [r1]    /*��0��ַд0*/
	ldr r2, [r1]    /*��ȡ0��ַ��ֵ*/
	cmp r1, r2      /*�Ƿ��д*/
	ldr sp, =4096+0x40000000   /*nor����*/
    ldreq sp, =4096  /*nand ����*/
    streq r0, [r1]
    bl sysclock_init	

	/*����CPU�������첽ģʽ*/
	mrc p15,0,r0,c1,c0,0
	orr r0,r0,#0XC0000000
	mcr p15,0,r0,c1,c0,0
	
	bl main

halt:
	b halt






