
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
	stmfd sp!, {r0-r12,lr}

	//bl system_call
		
	ldmfd sp!, {r0-r12,pc}^
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
	
  	//中断嵌套优化
/*	sub lr, lr, #4
	str lr, [sp, #-0x4]
	mrs lr, spsr
	str lr, [sp, #-0x8]
	mov r0, sp
	str r0, [sp, #-0xc]
	TO_SVCMOD
	str lr, [sp, #-0x8]
	ldr lr, [r0, #-0x4]
	str lr, [sp, #-0x4] //lr_irq
	ldr lr, [r0, #-0x8] //spsr
	ldr r0, [r0, #-0xc]
	sub sp, sp, #0x8
	stmfd sp!, {r0-r12,lr}//lr --spsr
	bl interrupt_process
	ldmfd sp!, {r0-r12,lr}
	msr spsr, lr
	ldmfd sp!, {lr,pc}^
*/	
fiq:
	nop
	

	



