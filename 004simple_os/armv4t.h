
#ifndef _ARMV4T_H_ 
#define _ARMV4T_H_


/*��ջ*/
.equ STACK_TOP,  0x1000 /*4KB*/

.equ NAND_BASE,  0
.equ NOR_BASE, 0x40000000

.equ SVC_STACK,  STACK_TOP
.equ FIQ_STACK, (SVC_STACK - 0x154)   /*340���ֽ�*/
.equ IRQ_STACK, (FIQ_STACK - 0x154)	
.equ UND_STACK, (IRQ_STACK - 0x154)	
.equ ABT_STACK, (UND_STACK - 0x154)
.equ SYS_STACK, (ABT_STACK - 0x154) /*usr sys*/	

/*ģʽ,CPSR�Ĵ���*/

.equ DISABLE_IRQ,   0x80 //1000 0000
.equ DISABLE_FIQ,	0x40 //0100 0000


.equ SVC_MOD,   0b10011
.equ FIQ_MOD,	0b10001
.equ IRQ_MOD,	0b10010
.equ UND_MOD,	0b11011
.equ ABT_MOD,	0b10111
.equ SYS_MOD,	0b11111
.equ USR_MOD,   0b10000
/*�궨��*/
/*CPU ����ģʽ*/

/*
cpsr
cpsr_c :cpsr�Ĵ����ĵ�8λ

c ������ (PSR [7:0]) 
x ��չ������ (PSR [15:8]) 
s ״̬������ (PSR [23:16]) 
f ��־������ (PSR [31:24])
*/

.macro TO_SVCMOD
	msr cpsr_c, #(DISABLE_IRQ | DISABLE_FIQ | SVC_MOD)
.endm

.macro TO_IRQMOD
	msr cpsr_c, #(DISABLE_IRQ | DISABLE_FIQ | IRQ_MOD)
.endm

.macro TO_FIQMOD
	msr cpsr_c, #(DISABLE_IRQ | DISABLE_FIQ | FIQ_MOD)
.endm

.macro TO_SYSMOD
	msr cpsr_c, #(DISABLE_IRQ | DISABLE_FIQ | SYS_MOD)
.endm

.macro TO_UNDMOD
	msr cpsr_c, #(DISABLE_IRQ | DISABLE_FIQ | UND_MOD)
.endm

.macro TO_ABTMOD
	msr cpsr_c, #(DISABLE_IRQ | DISABLE_FIQ | ABT_MOD)
.endm

.macro TO_USRMOD
	msr cpsr_c, #(DISABLE_IRQ | DISABLE_FIQ | USR_MOD)
.endm
#endif


