





.text

.global _start
.extern undef_ins
.extern swi
.extern abort_ins
.extern abort_data
.extern irq
.extern fiq



/**/

/*ģʽCPSR�Ĵ���*/

.equ DISABLE_IRQ,   0x80
.equ DISABLE_FIQ,	0x40


.equ SYS_MOD,	0b11111
.equ USR_MOD,   0b10000
.equ SVC_MOD,   0b10011
.equ FIQ_MOD,	0b10001
.equ IRQ_MOD,	0b10010
.equ UND_MOD,	0b11011
.equ ABT_MOD,	0b10111

/*��ջ*/
.equ STACK_TOP,  4096  /*4KB*/

.equ NAND_BASE,  0
.equ NOR_BASE, 0x40000000

.equ SVC_STACK,  STACK_TOP
.equ IRQ_STACK, (SVC_STACK - 100)   /*100���ֽ�*/
.equ FIQ_STACK, (IRQ_STACK - 100)	
.equ UND_STACK, (FIQ_STACK - 100)	
.equ ABT_STACK, (UND_STACK - 100)
.equ SYS_STACK, (ABT_STACK - 100)	

_start:
	/*�쳣������*/  
	/*
	����ģʽ: User(usr) FIQ(fiq) IRQ(irq) Supervisor(svc)����/����ģʽ Abort(abt) Undefined(und) System(sys)��Ȩģʽ
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
		
.align 2  /*αָ�����Ϊ2��ָ����*/

reset:

	/*�ؿ��Ź�*/	
	ldr r0, =0x53000000   /*WTCON*/	
	ldr r1, =0	
	str r1, [r0]
	
	/*��ʼ������ģʽ�µĶ�ջ,��ջ�ݼ���ʽ
	  �ϵ縴λ��cpu���ڹ���ģʽsvc
	*/
	/*�ж�norflash��������nandflash���� */
	/*
    nor flash������nor flashΪ0��ַ��
    nor flash��ʱ�ɶ�����д

    nand flash������nand flashǰ4KB���뿽����
    Ƭ��SRAM��
	*/
//	ldr r0, =0
//	ldr r1, =0
//	str r2, [r0]  /*����0��ַ����ֵ*/
//	ldr r1, [r0]  /*��0��ַ��д0*/
//	str r3, [r0]  /*��ȡ0��ַ����ֵ*/
//	cmp r3, r0   /*�ж��Ƿ�д�ɹ�*/
	/*д�ɹ�,Ϊnand flash����*/
//	streq r3, [r0] /*�ָ�0��ַ��ֵ*/ 
//	bne nor_start

/*	
nand_start:	
	//nand flash ���� 4K
	msr cpsr, #(DISABLE_IRQ | DISABLE_FIQ | SVC_MOD)
	ldr sp, =(SVC_STACK + NAND_BASE)

	msr cpsr, #(DISABLE_IRQ | DISABLE_FIQ | IRQ_MOD)
	ldr sp, =(IRQ_STACK + NAND_BASE)

	msr cpsr, #(DISABLE_IRQ | DISABLE_FIQ | FIQ_MOD)
	ldr sp, =(FIQ_STACK + NAND_BASE)

	msr cpsr, #(DISABLE_IRQ | DISABLE_FIQ | ABT_MOD)
	ldr sp, =(ABT_STACK + NAND_BASE)

	msr cpsr, #(DISABLE_IRQ | DISABLE_FIQ | UND_MOD)
	ldr sp, =(UND_STACK + NAND_BASE)

	msr cpsr, #(DISABLE_IRQ | DISABLE_FIQ | SYS_MOD)
	ldr sp, =(SYS_STACK + NAND_BASE)
	
	b  level1_init
*/	

nor_start:
	//nor flash ����/
	msr cpsr, #(DISABLE_IRQ | DISABLE_FIQ | SVC_MOD)
	ldr sp, =SVC_STACK + NOR_BASE 

	msr cpsr, #(DISABLE_IRQ | DISABLE_FIQ | IRQ_MOD)
	ldr sp, =IRQ_STACK + NOR_BASE

	msr cpsr, #(DISABLE_IRQ | DISABLE_FIQ | FIQ_MOD)
	ldr sp, =FIQ_STACK + NOR_BASE

	msr cpsr, #(DISABLE_IRQ | DISABLE_FIQ | ABT_MOD)
	ldr sp, =ABT_STACK + NOR_BASE

	msr cpsr, #(DISABLE_IRQ | DISABLE_FIQ | UND_MOD)
	ldr sp, =UND_STACK + NOR_BASE

	msr cpsr, #(DISABLE_IRQ | DISABLE_FIQ | SYS_MOD)
	ldr sp, =SYS_STACK + NOR_BASE

//	ldr sp, =4096+0x40000000   /*nor����*/
//	ldr sp, =4096
/*
bss_init:	
    //��bss��
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

   	/*����CPU�������첽ģʽ*/	
	mrc p15,0,r0,c1,c0,0	
	orr r0,r0,#0XC0000000	
	mcr p15,0,r0,c1,c0,0

	bl sysclock_init
	bl sdram_init
	bl copy2sdram
	bl bss_init
/*������*/
	ldr lr, =halt
	ldr pc, =main

halt:
	b halt
