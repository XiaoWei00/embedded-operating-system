


/*
���ֹ���ģʽ:
User
FIQ
IRQ
Supervisor
Abort mode
System
Undefined
*/
.text
.global _start

_start:

	/*�쳣������*/
	b reset     /*Supervisor�����ת*/
	

reset:
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

	/*����CPU�������첽ģʽ*/
	mrc p15,0,r0,c1,c0,0
	orr r0,r0,#0XC0000000
	mcr p15,0,r0,c1,c0,0
	
    bl sysclock_init	

	bl uart_init

	/*��ʼ��SDRM*/
	bl sdram_init

	bl nandflash_init
	
	/*�����ض�λ*/
    bl copy2sdram

	/*��bss��*/
	bl bss_init 
	/***��bss��***/
/*	ldr r0, =_bss_start
	ldr r1, =_end
	ldr r2, =0
bss_init:
    str r2, [r0]
	add	r0, r0, #4
	cmp r0, r1	
	ble bss_init
*/	
	//bl main  
	//ldr lr, =halt   /*?*/
	ldr pc, =main  /*������תָ��*/
	//ldr pc, =halt
	
halt:
	b halt






