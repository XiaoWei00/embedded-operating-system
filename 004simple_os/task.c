

#include "task.h"
#include "interrupt.h"
#include "lib.h"



static task_info *currentTask = NULL;
static u32 taskBase = 0x30100000;
static task_info kernelTask;

bool current_task_over(void)
{
	if(1)
	{
		return TRUE;	
	}

	return FALSE;
}


task_info *get_current_task_info(void)
{
	register u32 sp asm("sp");
	if(USER_TASK_SP(sp))
	{	
		
		return (task_info *)(sp & ~(TASK_SIZE - 1));
	}

	return &kernelTask;
}	

void task_init(void)
{
	currentTask = &kernelTask;
	currentTask->next = currentTask;
}	

u32 get_cpsr()
{
	u32 ret = 0;
	asm volatile(
	"mrs %0, cpsr\n\t"
	:"=r"(ret)
	:
	);
	return ret;
}	

u32 get_spsr()
{
	u32 ret = 0;
	asm volatile(
	"mrs %0, spsr\n\t"
	:"=r"(ret)
	:
	);
	return ret;
}
u32 do_fork(task_fun fun, void *args)
{


	
	task_info *newTaskinfo = (task_info *)(taskBase + TASK_SIZE);
	taskBase += TASK_SIZE;

	

	newTaskinfo->sp = (u32)(newTaskinfo) + TASK_SIZE - 4;
	

	
	u32 cpsr = get_cpsr();

	u32 sp = newTaskinfo->sp;
	NEWTASK_INIT(sp ,fun,args,0,cpsr);

 	newTaskinfo->sp = sp;

	disable_irq();
	task_info *tmp = currentTask->next;
	currentTask->next = newTaskinfo;
	newTaskinfo->next = tmp;
	enable_irq();

	return 0;
}	

task_info *common_schedule(void)
{
	task_info *ret = currentTask->next;
	currentTask = ret;
	return ret;
}



