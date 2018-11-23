
#include "armv4t.h"

.text
.global undef_ins
.global swi
.global abort_ins
.global abort_data
.global irq
.global fiq




undef_ins:
	nop
		
swi:

	str lr, [sp, #-0x4]
	
	mrs lr, spsr
	str lr, [sp, #-0x8]
	
	
	str r0, [sp, #-0xc]
	mov r0, sp
	
	TO_SYSMOD

	str lr, [sp, #-0x8]
	
	ldr lr, [r0, #-0x4]
	str lr, [sp, #-0x4] //
	
	ldr lr, [r0, #-0x8] //spsr
	ldr r0, [r0, #-0xc]
	sub sp, sp, #0x8

	stmfd sp!, {r0-r12,lr}//lr --spsr

	ldr r0, [sp, #0x3c] 
	sub r0, r0, #4
	ldr r0, [r0]
	
	ldr r1, [sp, #0x48] 
	ldr r2, [sp, #0x44]  
	ldr r3, [sp, #0x38]
	
	bl system_call

	str r0, [sp, #64] 
	
	ldmfd sp!, {r0-r12,lr}

	msr spsr, lr
	ldmfd sp!, {lr,pc}^
	

abort_ins:
	nop
		
abort_data:
	nop

irq:

  //中断
/*  
	sub lr, lr, #4
	stmfd sp!, {r0-r12,lr}
  	bl interrupt_process
  	ldmfd sp!, {r0-r12,pc}^
*/
   
  //中断嵌套
/*  
	sub lr, lr, #4
	stmfd sp!, {lr}
	mrs lr, spsr
	stmfd sp!, {lr}	
	
	TO_SVCMOD
	stmfd sp!, {r0-r12}
	bl interrupt_process
	ldmfd sp!, {r0-r12}
	TO_IRQMOD
	ldmfd sp!, {lr}
	msr spsr, lr 
	ldmfd sp!, {pc}^
*/	
  	//中断嵌套优化
	sub lr, lr, #4
	
	str lr, [sp, #-0x4]
	
	mrs lr, spsr
	str lr, [sp, #-0x8]
	
	
	str r0, [sp, #-0xc]
	mov r0, sp
	
	TO_SVCMOD
/*
lr_irq  ---pc_sys/usr
r12
||
r0  ---sys/usr
spsr_irq---cpsr_sys/usr
*/
 
	
	ldr lr, [r0, #-0x4]
	str lr, [sp, #-0x4] //lr_irq
	
	ldr lr, [r0, #-0x8] //spsr_irq
	
	ldr r0, [r0, #-0xc]
	

	sub sp, sp, #0x4
	
	stmfd sp!, {r0-r12}

	sub sp, sp, #0x4
	str lr, [sp] //lr ---spsr

	bl interrupt_process

	ldr lr, [sp]
	add sp, sp, #0x4
	
	ldmfd sp!, {r0-r12}
	
	msr spsr, lr
	ldmfd sp!, {pc}^

fiq:
	nop
	

	



