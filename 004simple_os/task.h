

#ifndef _TASK_H_ 
#define _TASK_H_


#include "type.h"


typedef int (*task_fun)(void *);

typedef struct task_info_t task_info;

struct task_info_t{
	u32 sp;
	task_info *next;
};

#define NEWTASK_INIT(sp,fun,args,lr,cpsr)  do{ \
	(sp) = (sp) - 4;	\
	*((volatile u32 *)(sp)) = (u32)(fun); \
	(sp) = (sp) - 4;	\
	*((volatile u32 *)(sp)) = (u32)(lr); \
	(sp) = (sp) - 4 * 13;\
	*((volatile u32 *)(sp)) = (u32)(args); \
	(sp) = (sp) - 4;	\
	*((volatile u32 *)(sp)) = (u32)(cpsr); \
	}while(0)

#define TASK_SIZE 4096
#define USER_TASK_SP(sp)  ((sp) >  0x30100000 && (sp) < 0X30300000 )

void task_init(void);
u32 do_fork(task_fun fun, void * args);
bool current_task_over(void);
task_info *get_current_task_info(void);

u32 get_cpsr(void);

#endif


