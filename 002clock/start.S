





.text
.global _start

_start:

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
    bl sysclock_init	

	/*设置CPU工作于异步模式*/
	mrc p15,0,r0,c1,c0,0
	orr r0,r0,#0XC0000000
	mcr p15,0,r0,c1,c0,0
	
	bl main

halt:
	b halt







