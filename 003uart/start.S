


/*
七种工作模式:
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

	/*异常向量表*/
	b reset     /*Supervisor相对跳转*/
	nop
	nop
	nop
	nop
	nop
	ldr pc, _irq
	nop


_irq:
	.word irq

		
.align 2  /*伪指令，参数为2的指数幂*/


irq:
	sub lr, lr, #4
	stmfd sp!, {r0-r12,lr}
  	bl interrupt_process
  	ldmfd sp!, {r0-r12,pc}^


	
reset:
	/*关看门狗*/
	ldr r0, =0x53000000   /*WTCON*/
	ldr r1, =0
	str r1, [r0]

    /*设置栈，sp栈指针*/
	/*判断nor flash启动 还是nand flash启动*/
	/*向0地址写值，可写为nand启动，不可写为nor启动*/
	ldr r1, =0
	ldr r0, [r1]    /*保存0地址的值到r0*/
	str r1, [r1]    /*向0地址写0*/
	ldr r2, [r1]    /*读取0地址的值*/
	cmp r1, r2      /*是否可写*/
	ldr sp, =4096+0x40000000   /*nor启动*/
    ldreq sp, =4096  /*nand 启动*/
    streq r0, [r1]

	/*设置CPU工作于异步模式*/
	mrc p15,0,r0,c1,c0,0
	orr r0,r0,#0XC0000000
	mcr p15,0,r0,c1,c0,0
	
    bl sysclock_init	

	bl uart_init

	/*初始化SDRM*/
	bl sdram_init

	bl nandflash_init
	
	/*代码重定位*/
    bl copy2sdram

	/*清bss段*/
	bl bss_init 
	/***清bss段***/
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
	ldr pc, =main  /*绝对跳转指令*/
	//ldr pc, =halt
	
halt:
	b halt







