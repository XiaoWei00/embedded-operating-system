


.text
.global undef_ins
.global swi
.global abort_ins
.global abort_data
.global irq
.global fiq
.global enable_irq
.global disable_irq

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
	sub lr, lr , #4
	stmfd sp!, {r0-r12,lr}

	bl interrupt_process

	ldmfd sp!, {r0-r12,pc}^	
fiq:
	nop
	

	



