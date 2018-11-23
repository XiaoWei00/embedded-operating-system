



#include "armv4t.h"



.text
.global _start
.extern undef_ins
.extern swi
.extern abort_ins
.extern abort_data
.extern irq
.extern fiq

_start:
	/*异常向量表*/  
	/*
	七种模式: User(usr) FIQ(fiq) IRQ(irq) Supervisor(svc)管理/保护模式 Abort(abt) Undefined(und) System(sys)特权模式
	*/
	b reset   				/*Reset  Supervisor*/
	ldr pc, _undef_ins 		/*Undefined instruction  Undefined*/ 
	ldr pc, _swi  			/*Software interrupt Supervisor*/ 
	ldr pc, _abort_ins		/*Abort prefetch     Abort*/
	ldr pc, _abort_data		/*Abort data      Abort*/
	nop						/*Reserved*/
	ldr pc, _irq			/*IRQ    IRQ*/
	ldr pc, _fiq			/*FIQ   FIQ*/
	
_undef_ins:
	.word undef_ins
_swi:
	.word swi
_abort_ins:
	.word abort_ins
_abort_data:
	.word abort_data
_irq:
	.word irq
_fiq:
	.word fiq
		
.align 2  /*伪指令，参数为2的指数幂*/

reset:

	/*关看门狗*/	
	ldr r0, =0x53000000   /*WTCON*/	
	ldr r1, =0	
	str r1, [r0]
	
	/*初始化各个模式下的堆栈,满栈递减方式
	  上电复位，cpu处于管理模式svc
	*/
	/*判断norflash启动还是nandflash启动 */
	/*
    nor flash启动，nor flash为0地址，
    nor flash此时可读不可写

    nand flash启动，nand flash前4KB代码拷贝到
    片内SRAM中
	*/
	ldr r0, =0
	ldr r1, =0
	str r2, [r0]  /*保存0地址处数值*/
	ldr r1, [r0]  /*向0地址处写0*/
	str r3, [r0]  /*读取0地址处数值*/
	cmp r3, r0   /*判断是否写成功*/
	/*写成功,为nand flash启动*/
	streq r3, [r0] /*恢复0地址数值*/ 
	bne nor_start


nand_start:	
	//nand flash 启动 4K
	TO_SVCMOD
	ldr sp, =(SVC_STACK + NAND_BASE)

	TO_IRQMOD
	ldr sp, =(IRQ_STACK + NAND_BASE)

	TO_FIQMOD
	ldr sp, =(FIQ_STACK + NAND_BASE)

	TO_ABTMOD
	ldr sp, =(ABT_STACK + NAND_BASE)

	TO_UNDMOD
	ldr sp, =(UND_STACK + NAND_BASE)

	TO_SYSMOD
	ldr sp, =(SYS_STACK + NAND_BASE)

	
	
	b  level1_init


nor_start:
	//nor flash 启动/
	TO_SVCMOD
	ldr sp, =(SVC_STACK + NOR_BASE) 

	TO_IRQMOD
	ldr sp, =(IRQ_STACK + NOR_BASE)

	TO_FIQMOD
	ldr sp, =(FIQ_STACK + NOR_BASE)

	TO_ABTMOD
	ldr sp, =(ABT_STACK + NOR_BASE)

	TO_UNDMOD
	ldr sp, =(UND_STACK + NOR_BASE)

	TO_SYSMOD
	ldr sp, =(SYS_STACK + NOR_BASE)


//	ldr sp, =4096+0x40000000   /*nor启动*/
//	ldr sp, =4096
/*
bss_init:	
    //清bss段
	ldr r0, =bss_start
	ldr r1, =bss_end
	ldr r2, =0
   
clear_bss:    
	str r2, [r0]	
	add r0, r0, #4	 
	cmp r0, r1
	ble clear_bss
*/
level1_init:

   	/*设置CPU工作于异步模式*/	
	mrc p15,0,r0,c1,c0,0	
	orr r0,r0,#0XC0000000	
	mcr p15,0,r0,c1,c0,0

	bl sysclock_init
	bl sdram_init
	bl nandflash_init
	bl copy2sdram
	bl bss_init

//	TO_USRMOD
/*主程序*/
	ldr lr, =halt
	ldr pc, =main

halt:
	b halt

