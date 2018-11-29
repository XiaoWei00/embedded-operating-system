
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
/*
	sub sp, sp, #0xc	
	mov r0, lr 
	bl uart_send_byte // 2 D0
	
	ldr r0, [sp, #0x4]
	bl uart_send_byte // 3
	add sp, sp, #0xc
*/

	mov r0, sp
	
	TO_SYSMOD

	str lr, [sp, #-0x8]
	
	ldr lr, [r0, #-0x4]
	str lr, [sp, #-0x4] //
	
	ldr lr, [r0, #-0x8] //spsr
	sub sp, sp, #0x8
	
/*	
	mov r0, lr
	bl uart_send_byte // 
*/	

	
	ldr r0, [r0, #-0xc]
	stmfd sp!, {r0-r12}//lr --spsr

	sub sp, sp, #0x4
	str lr, [sp]
/*	
	mov r0, lr
	bl uart_send_byte //  4
*/

	
/*	
	ldr r0, [sp] 
	bl uart_send_byte // 5
*/
	
/*
	mov r0, sp
	ldr r1, =1	
	bl stack_print
*/	
	ldr r0, [sp, #0x3c] //60  
	sub r0, r0, #4
	ldr r0, [r0]
	
	ldr r1, [sp, #0x48] //72 pnum
	ldr r2, [sp, #0x44]  //68 pdata 

	bl system_call
	str r0, [sp, #64] 

/*
	mov r0, sp
	ldr r1, =1	
	bl stack_print
*/
/*
	ldr r0, [sp]
	bl uart_send_byte // 6 
*/	
//	ldmfd sp!, {lr}

	ldr lr, [sp]
	add sp, sp, #0x4
	
//	msr spsr, lr
/*		
	mov r0, lr
	bl uart_send_byte // 7
*/

// 
	
	mov r0, lr // spsr_usr
	bl usr_irq
	
	msr cpsr, r0
/*
	stmfd sp!, {r0}	
	mov	r0, lr
	bl uart_send_byte
	ldmfd sp!, {r0}
*/	
	ldmfd sp!, {r0-r12,lr,pc}
	

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
	

	



