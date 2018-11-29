
#include "armv4t.h"



.text
.global task_schedule

task_schedule:

	TO_SYSMOD
/*
lr_irq
lr_sys/usr
*/
//preserve  the scene of current task, SVC stack---task stack 

	str lr, [sp, #-0x8]	//lr_sys/usr
	
	ldr r0, =(SVC_STACK + NAND_BASE)
	
	ldr lr, [r0, #-0x4]
	str lr, [sp, #-0x4]  //lr_irq


	sub sp, sp, #0x8

	sub r0, r0,#0x4 

	ldr r1, =56
	
preserve_scene:
	
	sub r0, r0, #0x4
	ldr lr, [r0]
	
	sub sp, sp, #0x4
	str lr, [sp]
	
	sub r1, r1, #4
	cmp r1, #0  //´óÓÚ0 Ìø×ª
	bne  preserve_scene


//update task sp
//C  return task->sp 

	bl get_current_task_info

	str sp, [r0]

/*
//don't update the kernel task sp
	mov r1, sp
	bic r1, #0xff0
	bic r1, #0xf
	mov r0, sp
	str r0, [r1]
*/	
	
	bl common_schedule

//clear interrupt processing in SVC mode
//default nand flash start
	TO_SVCMOD
	
	ldr sp, =(SVC_STACK + NAND_BASE)

//resume the scene of the next task
/*
pc
lr
r12
|
r0
cpsr
*/
	TO_SYSMOD
	
	ldr sp, [r0]
	
	ldr r1, [sp]
	add sp, sp, #0x4

	msr cpsr,r1
	
	ldmfd sp!, {r0-r12,lr,pc}
	
	
	
	
		
	
	
	

	

